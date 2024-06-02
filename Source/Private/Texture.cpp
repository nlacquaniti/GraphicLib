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

Texture::~Texture() noexcept {
    if (!_id.IsInitialised) {
        return;
    }

    Bind();
    GraphicAPI::Get().GetTextureImpl().Delete(_id.Value, _data.Type);
}

void Texture::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("");
        return;
    }

    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(1);
    }

    GraphicAPI::Get().GetTextureImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void Texture::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetTextureImpl().Bind(_id.Value, _data.Type);
}

void Texture::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetTextureImpl().Unbind(_id.Value, _data.Type);
}

void Texture::ActivateUnit(unsigned int slot) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetTextureImpl().ActivateUnit(_id.Value, _data.Type, slot);
}

void Texture::Set(ETextureType type, std::string&& texturePath, std::vector<TextureParam>&& params) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

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
    GraphicAPI::Get().GetTextureImpl().Set(_id.Value, _data, pixelData);
    stbi_image_free(pixelData);
}

void Texture::Set(ETextureType type, const SetTextureParams& setParams, std::vector<TextureParam>&& params) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

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
    GraphicAPI::Get().GetTextureImpl().Set(_id.Value, _data, nullptr);
}

const TextureData& Texture::GetData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _data;
}

unsigned int Texture::GetID() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _id.Value;
}
}; // namespace GraphicLib
