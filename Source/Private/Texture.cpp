#include "GraphicLib/Texture.h"

#include "InternalLogger.h"
#include "OpenGLImpl/TextureImpl.h"
#include "OpenGLImpl/Utils/TextureImplUtils.h"
#include "StbImage.h"
#include <filesystem>
#include <format>
#include <string>

namespace GraphicLib {
namespace {
std::string extractTextureName(const std::string& texturePath) {
    const size_t nameEndPos = texturePath.rfind('.');
    if (nameEndPos == std::string::npos) {
        const std::string& logText =
            std::format("Can't extract texture name for file \"{}\"", texturePath);
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
        const std::string& logText =
            std::format("Texture name is empty for file \"{}\"", texturePath);
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
    Internal::DeleteTexture(&_id.Value);
}

void Texture::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(1);
    }

    Internal::InitialiseTexture(&_id.Value);
    _id.IsInitialised = true;
}

void Texture::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    unsigned int outType;
    if (!Internal::ConvertTextureType(_data.Type, outType)) {
        return;
    }

    Internal::BindTexture(_id.Value, outType);
}

void Texture::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    unsigned int outType;
    if (!Internal::ConvertTextureType(_data.Type, outType)) {
        return;
    }

    Internal::UnbindTexture(_id.Value, outType);
}

void Texture::SetTextureSlot(unsigned int slot) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    const auto maxTextureSlots =
        static_cast<unsigned int>(Internal::GetMaxTextureSlots());
    if (slot > maxTextureSlots) {
        const std::string& logText = std::format(
            "Provided texture slot {} exceeded the max number of texture slots {}", slot,
            maxTextureSlots);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    Internal::SetTextureSlot(slot);
}

void Texture::Set(TextureData&& data) {
    static_assert(TextureData::TEXTURE_PARAMETER_MAX_COUNT ==
                  Internal::TextureData::MAX_PARAMETERS_COUNT);

    if (!data.FilePath.empty()) {
        _setFromFile(std::move(data));
    } else {
        _setRaw(std::move(data));
    }
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

void Texture::_setFromFile(TextureData&& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (data.Parameters.empty()) {
        LOG_INTERNAL_ERROR("Texture parameters must be set");
        return;
    }

    if (data.Type == ETextureType::NONE) {
        LOG_INTERNAL_ERROR("TextureType must be set");
        return;
    }

    if (!std::filesystem::exists(std::filesystem::path{data.FilePath})) {
        const std::string& logText =
            std::format("File \"{}\" doesn't exist", data.FilePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    const std::string name = extractTextureName(data.FilePath);
    if (name.empty()) {
        const std::string& logText =
            std::format("File \"{}\" resulted in an empty name", data.FilePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    int width, height, channel;
    unsigned char* pixelData =
        stbi_load(data.FilePath.c_str(), &width, &height, &channel, 0);
    if (stbi_failure_reason() != nullptr) {
        const std::string& logText =
            std::format(R"(stbi_load failed with reason "{}")", stbi_failure_reason());
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (pixelData == nullptr) {
        const std::string& logText =
            std::format(R"(Can't read pixel data for "{}")", data.FilePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (width == 0) {
        const std::string& logText = std::format(
            R"(File "{}" with name "{}" couldn't retrive width)", data.FilePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (height == 0) {
        const std::string& logText = std::format(
            R"(File "{}" with name "{}" couldn't retrive height)", data.FilePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    if (channel == 0) {
        const std::string& logText = std::format(
            R"(File "{}" with name "{}" couldn't retrive channel)", data.FilePath, name);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _data.Parameters = std::move(data.Parameters);
    _data.FilePath = std::move(data.FilePath);
    _data.Name = std::move(name);
    _data.PixelData = pixelData;
    _data.Width = width;
    _data.Height = height;
    _data.Type = data.Type;
    _data.Channel = static_cast<ETextureChannel>(channel);
    _data.Format = ETextureFormat::RGBA32F;
    _data.DataType = ETextureDataType::UNSIGNED_BYTE;

    Internal::TextureData internalTextureData;
    if (!Internal::ConvertTextureData(_data, internalTextureData)) {
        return;
    }

    Bind();
    Internal::SetTexture(internalTextureData);
    Unbind();
}

void Texture::_setRaw(TextureData&& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (data.Parameters.empty()) {
        LOG_INTERNAL_ERROR("Texture parameters must be set");
        return;
    }

    if (data.Name.empty()) {
        LOG_INTERNAL_ERROR("Texture name must be set");
        return;
    }

    if (data.Width == 0) {
        LOG_INTERNAL_ERROR("Texture width must be set");
        return;
    }

    if (data.Height == 0) {
        LOG_INTERNAL_ERROR("Texture height must be set");
        return;
    }

    if (data.Type == ETextureType::NONE) {
        LOG_INTERNAL_ERROR("TextureType must be set");
        return;
    }

    if (data.Channel == ETextureChannel::NONE) {
        LOG_INTERNAL_ERROR("Texture channel must be set");
        return;
    }

    if (data.Format == ETextureFormat::NONE) {
        LOG_INTERNAL_ERROR("Texture format must be set");
        return;
    }

    if (data.DataType == ETextureDataType::NONE) {
        LOG_INTERNAL_ERROR("Texture data type must be set");
        return;
    }

    _data.Parameters = std::move(data.Parameters);
    _data.FilePath = {};
    _data.Name = std::move(data.Name);
    _data.PixelData = {};
    _data.Width = data.Width;
    _data.Height = data.Height;
    _data.Type = data.Type;
    _data.Channel = data.Channel;
    _data.Format = data.Format;
    _data.DataType = data.DataType;

    Internal::TextureData internalTextureData;
    if (!Internal::ConvertTextureData(_data, internalTextureData)) {
        return;
    }

    Bind();
    Internal::SetTexture(internalTextureData);
    Unbind();
}
}; // namespace GraphicLib
