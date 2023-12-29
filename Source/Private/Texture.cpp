#include "GraphicLib/Texture.h"

#include "InternalLogger.h"
#include "StbImage.h"
#include <filesystem>
#include <fmt/format.h>
#include <string>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
Texture::~Texture() {
    stbi_image_free(_pixelData);
    _pixelData = nullptr;
    Delete();
}

void Texture::Initialise(ETextureType type) {
    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(true);
    }
    _data.Type = type;
    GraphicAPI::Get().GetTextureImpl().Initialise(_id);
}

void Texture::Bind() {
    GraphicAPI::Get().GetTextureImpl().Bind(_id, _data.Type);
}

void Texture::Unbind() {
    GraphicAPI::Get().GetTextureImpl().Unbind(_id, _data.Type);
}

void Texture::Draw(unsigned char slot) {
    GraphicAPI::Get().GetTextureImpl().Draw(_id, _data.Type, slot);
    Bind();
}

void Texture::Set(const char* texturePath, const Span<TextureParam>& params) {
    const std::filesystem::path filePath{texturePath};
    if (!std::filesystem::exists(filePath)) {
        const std::string& logText = fmt::format("File \"{}\" doesn't exist", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _pixelData = stbi_load(std::filesystem::absolute(filePath).string().c_str(), &_data.Width, &_data.Height, reinterpret_cast<int*>(&_data.Channel), 0);
    if (_pixelData == nullptr) {
        const std::string& logText = fmt::format("Can't read pixel data for \"{}\"", texturePath);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    _data.PixelData.SetData(_pixelData, sizeof(unsigned char) * static_cast<unsigned long long>(_data.Width * _data.Height * static_cast<int>(_data.Channel)));
    _data.FilePath.SetData({texturePath, strlen(texturePath) + 1});
    _data.Format = ETextureFormat::RGBA32F;
    _data.DataType = ETextureDataType::UNSIGNED_BYTE;
    _data.Parameters.SetData(params);

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id, _data);
}

void Texture::Set(const SetTextureParams& setParams, const Span<TextureParam>& params) {
    _data.Width = setParams.Width;
    _data.Height = setParams.Height;
    _data.Channel = setParams.Channel;
    _data.Format = setParams.Format;
    _data.DataType = setParams.DataType;
    _data.Parameters.SetData(params);

    Bind();
    GraphicAPI::Get().GetTextureImpl().Set(_id, _data);
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
