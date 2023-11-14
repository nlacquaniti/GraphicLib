#include "GraphicLib/Texture.h"

#include "InternalLogger.h"
#include "StbImage.h"
#include <string.h>
#include <filesystem>
#include <sstream>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/TextureImpl.h"
using TextureImpl = GraphicLib::OpenGLImpl::TextureImpl;
#else
#error "No VertexBufferImpl has been detected."
#endif

namespace GraphicLib {
Texture::~Texture() {
    stbi_image_free(_pixelData);
    _pixelData = nullptr;
    _data.PixelData = {};
}

void Texture::Initialise() {
    static bool stbiFlippedVertically{};
    if (!stbiFlippedVertically) {
        stbiFlippedVertically = true;
        stbi_set_flip_vertically_on_load(true);
    }
    TextureImpl::Initialise(_id);
}

void Texture::Bind() {
    TextureImpl::Bind(_id, _data.Type);
}

void Texture::Unbind() {
    TextureImpl::Unbind(_id, _data.Type);
}

void Texture::Draw(unsigned char slot) {
    TextureImpl::Draw(_id, _data.Type, slot);
}

void Texture::Set(const char* texturePath, TextureType type, const Span<TextureParam>& params) {
    const std::filesystem::path filePath{texturePath};
    if (!std::filesystem::exists(filePath)) {
        std::stringstream logText;
        logText << "File \"" << texturePath << "\" doesn't exist";
        LOG_INTERNAL_ERROR(logText.str().c_str());
        return;
    }

    _pixelData = stbi_load(std::filesystem::absolute(filePath).string().c_str(), &_data.Width, &_data.Height, reinterpret_cast<int*>(&_data.Channel), 0);
    if (_pixelData == nullptr) {
        std::stringstream logText;
        logText << "Can't read pixel data for \"" << texturePath << "\"";
        LOG_INTERNAL_ERROR(logText.str().c_str());
        return;
    }
    _data.PixelData.SetData(_pixelData, sizeof(unsigned char) * static_cast<unsigned long long>(_data.Width * _data.Height * static_cast<int>(_data.Channel)));
    _data.FilePath.SetData({texturePath, strlen(texturePath) + 1});
    _data.Type = type;
    _data.Parameters.SetData(params);

    TextureImpl::Set(_id, _data);
}

const TextureData& Texture::GetData() const {
    return _data;
}

unsigned int Texture::GetID() const {
    return _id;
}
}; // namespace GraphicLib
