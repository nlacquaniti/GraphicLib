#include "GraphicLib/Texture.h"

#include "FmtFormat.h"
#include "InternalLogger.h"
#include "StbImage.h"
#include <filesystem>
#include <string>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
namespace {
std::string extractTextureName(const std::string& texturePath) {
    const size_t nameEndPos = texturePath.rfind('.');
    if (nameEndPos == std::string::npos) {
        const std::string& logText = fmt::format("Can't extract texture name for file \"{}\"", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return {};
    }

    size_t nameStartPos = texturePath.rfind('/');
    if (nameStartPos == std::string::npos) {
        nameStartPos = 0;
    } else {
        ++nameStartPos;
    }

    size_t nameSize = nameEndPos - nameStartPos;

    std::string textureName = texturePath.substr(nameStartPos, nameSize);
    if (textureName.empty()) {
        const std::string& logText = fmt::format("Texture name is empty for file \"{}\"", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return {};
    }

    return textureName;
}
} // namespace

Texture::Texture() noexcept {
    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(1);
    }

    GraphicAPI::Get().GetTextureImpl().Initialise(_id);
}

Texture::~Texture() noexcept {
    Delete();
}

void Texture::Bind() const {
    GraphicAPI::Get().GetTextureImpl().Bind(_id, _data.Type);
}

void Texture::Unbind() const {
    GraphicAPI::Get().GetTextureImpl().Unbind(_id, _data.Type);
}

void Texture::ActivateUnit(unsigned int slot) const {
    GraphicAPI::Get().GetTextureImpl().ActivateUnit(_id, _data.Type, slot);
}

void Texture::Set(ETextureType type, std::string&& texturePath, std::vector<TextureParam>&& params) {
    const std::filesystem::path filePath{texturePath};
    if (!std::filesystem::exists(filePath)) {
        const std::string& logText = fmt::format("File \"{}\" doesn't exist", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    std::string textureName = extractTextureName(texturePath);
    if (textureName.empty()) {
        return;
    }

    int textureWidth{};
    int textureHeight{};
    int textureChannel{};
    unsigned char* pixelData = stbi_load(std::filesystem::absolute(filePath).string().c_str(), &textureWidth, &textureHeight, &textureChannel, 0);
    if (pixelData == nullptr) {
        const std::string& logText = fmt::format("Can't read pixel data for \"{}\"", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _data.FilePath = std::move(texturePath);
    _data.Name = std::move(textureName);
    _data.Parameters = std::move(params);
    _data.Width = textureWidth;
    _data.Height = textureHeight;
    _data.Type = type;
    _data.Channel = static_cast<ETextureChannel>(textureChannel);
    _data.Format = ETextureFormat::RGBA32F;
    _data.DataType = ETextureDataType::UNSIGNED_BYTE;

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id, _data, pixelData);
    stbi_image_free(pixelData);
}

void Texture::Set(ETextureType type, const SetTextureParams& setParams, std::vector<TextureParam>&& params) {
    if (setParams.Name.empty()) {
        const std::string& logText{"Texture name is empty"};
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _data.FilePath = {};
    _data.Name = setParams.Name;
    _data.Parameters = std::move(params);
    _data.Width = setParams.Width;
    _data.Height = setParams.Height;
    _data.Type = type;
    _data.Channel = setParams.Channel;
    _data.Format = setParams.Format;
    _data.DataType = setParams.DataType;

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id, _data, nullptr);
}

void Texture::Delete() {
    Bind();
    GraphicAPI::Get().GetTextureImpl().Delete(_id, _data.Type);
}

const TextureData& Texture::GetData() const {
    return _data;
}

unsigned int Texture::GetID() const {
    return _id;
}
}; // namespace GraphicLib
