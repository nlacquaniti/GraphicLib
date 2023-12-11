#include "OpenGLImpl/TextureImpl.h"

#include "OpenGLImpl/Utils/TextureImplUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <sstream>

namespace GraphicLib {
namespace OpenGLImpl {
int TextureImpl::_maxTextureSlots{-1};

void TextureImpl::Initialise(unsigned int& id) const {
    if (_maxTextureSlots == -1) {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        std::stringstream logText;
        logText << "Max number of texture slots " << _maxTextureSlots;
        LOG_INTERNAL_NOTIFICATION(logText.str().c_str());
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
        std::stringstream logText;
        logText << "Provided texture slot " << slot << " exceeded the max number of texture slots " << _maxTextureSlots;
        LOG_INTERNAL_ERROR(logText.str().c_str());
        return;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
    Bind(id, type);
}

void TextureImpl::Set(unsigned int id, const TextureData& textureData) const {
    Bind(id, textureData.Type);

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
    Bind(id, type);
    glDeleteTextures(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
