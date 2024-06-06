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
    stbi_image_free(_data.PixelData);
    _data.PixelData = nullptr;
    Bind();
    GraphicAPI::Get().GetTextureImpl().Delete(_id.Value, _data.Type);
}

void Texture::Initialise(ETextureType type) {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(1);
    }
    _data.Type = type;
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

void Texture::Draw(unsigned int slot) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetTextureImpl().Draw(_id.Value, _data.Type, slot);
    Bind();
}

void Texture::Set(std::string&& texturePath, std::vector<TextureParam>&& params) {
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

    std::string name = extractTextureName(texturePath);
    if (name.empty()) {
        const std::string& logText = fmt::format("File \"{}\" resulted in an empty name", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    int width, height, channel;
    unsigned char* pixelData = stbi_load(texturePath.c_str(), &width, &height, &channel, 0);
    if (stbi_failure_reason() != nullptr) {
        const std::string& logText = fmt::format(R"(stbi_load failed with reason "{}")", stbi_failure_reason());
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (pixelData == nullptr) {
        const std::string& logText = fmt::format(R"(Can't read pixel data for "{}")", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (width == 0) {
        const std::string& logText = fmt::format(R"(File "{}" with name "{}" couldn't retrive width)", texturePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (height == 0) {
        const std::string& logText = fmt::format(R"(File "{}" with name "{}" couldn't retrive height)", texturePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (channel == 0) {
        const std::string& logText = fmt::format(R"(File "{}" with name "{}" couldn't retrive channel)", texturePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _data.Parameters = std::move(params);
    _data.FilePath = std::move(texturePath);
    _data.Name = std::move(name);
    _data.PixelData = pixelData;
    _data.Width = width;
    _data.Height = height;
    _data.Channel = static_cast<ETextureChannel>(channel);
    _data.Format = ETextureFormat::RGBA32F;
    _data.DataType = ETextureDataType::UNSIGNED_BYTE;

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id.Value, _data);
}

void Texture::Set(const SetTextureParams& setParams, std::vector<TextureParam>&& params) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    _data.Parameters = std::move(params);
    _data.FilePath = {};
    _data.Name = setParams.Name;
    _data.PixelData = {};
    _data.Width = setParams.Width;
    _data.Height = setParams.Height;
    _data.Channel = setParams.Channel;
    _data.Format = setParams.Format;
    _data.DataType = setParams.DataType;

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id.Value, _data);
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
