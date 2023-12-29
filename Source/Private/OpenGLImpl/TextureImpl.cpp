#include "OpenGLImpl/TextureImpl.h"

#include "InternalLogger.h"
#include "OpenGLImpl/Utils/TextureImplUtils.h"
#include <fmt/format.h>
#include <string>
#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
int TextureImpl::_maxTextureSlots{-1};

void TextureImpl::Initialise(unsigned int& id) const {
    if (_maxTextureSlots == -1) {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        const std::string& logText = fmt::format("Max number of texture slots {}", _maxTextureSlots);
        LOG_INTERNAL_NOTIFICATION(logText.c_str());
    }
    glGenTextures(1, &id);
}

void TextureImpl::Bind(unsigned int id, ETextureType type) const {
    unsigned int target{};
    if (!TextureImplUtils::ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, id);
}

void TextureImpl::Unbind(unsigned int, ETextureType type) const {
    unsigned int target{};
    if (!TextureImplUtils::ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, 0);
}

void TextureImpl::Draw(unsigned int id, ETextureType type, unsigned char slot) const {
    if (slot > _maxTextureSlots) {
        const std::string& logText = fmt::format("Provided texture slot {} exceeded the max number of texture slots {}", slot, _maxTextureSlots);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
}

void TextureImpl::Set(unsigned int id, const TextureData& textureData) const {
    unsigned int target{};
    if (!TextureImplUtils::ConvertTextureType(textureData.Type, target)) {
        return;
    }

    int internalFormat{};
    if (!TextureImplUtils::ConvertTextureFormat(textureData.Format, internalFormat)) {
        return;
    }

    unsigned int textureFormat{};
    if (!TextureImplUtils::ConvertTextureChannel(textureData.Channel, textureFormat)) {
        return;
    }

    unsigned int textureDataType{};
    if (!TextureImplUtils::ConvertTextureDataType(textureData.DataType, textureDataType)) {
        return;
    }

    // Assign texture Parameters.
    for (unsigned long long i{}; i < textureData.Parameters.Size(); ++i) {
        const TextureParam& param = textureData.Parameters[i];

        unsigned int paramName{};
        if (!TextureImplUtils::ConvertTextureParamName(param.Name, paramName)) {
            return;
        }

        int paramValue{};
        if (!TextureImplUtils::ConvertTextureParamValue(param.Value, paramValue)) {
            return;
        }

        glTexParameteri(target, paramName, paramValue);
    }

    glTexImage2D(target, 0, internalFormat, textureData.Width, textureData.Height, 0, textureFormat, textureDataType, textureData.PixelData.Data());
    glGenerateMipmap(target);
}

void TextureImpl::Delete(unsigned int& id, ETextureType type) const {
    glDeleteTextures(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
