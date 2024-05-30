#include "OpenGLImpl/TextureImpl.h"

#include "FmtFormat.h"
#include "InternalLogger.h"
#include "OpenGLImpl/Utils/TextureImplUtils.h"
#include <glad/glad.h>
#include <string>

namespace GraphicLib::OpenGLImpl {
unsigned int TextureImpl::_maxTextureSlots{0};

void TextureImpl::Initialise(unsigned int& id) {
    static bool _isMaxTextureSlotsInitialised = false;
    if (!_isMaxTextureSlotsInitialised) {
        int maxTextureSlots{};
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
        _maxTextureSlots = static_cast<unsigned int>(maxTextureSlots);
        const std::string& logText = fmt::format("Max number of texture slots {}", _maxTextureSlots);
        LOG_INTERNAL_NOTIFICATION(logText.c_str());
    }
    glGenTextures(1, &id);
    _isMaxTextureSlotsInitialised = true;
}

void TextureImpl::Bind(unsigned int id, ETextureType type) {
    unsigned int target{};
    if (!TextureImplUtils::ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, id);
}

void TextureImpl::Unbind(unsigned int /*unused*/, ETextureType type) {
    unsigned int target{};
    if (!TextureImplUtils::ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, 0);
}

void TextureImpl::ActivateUnit(unsigned int /*unused*/, ETextureType /*unused*/, unsigned int slot) {
    if (slot > _maxTextureSlots) {
        const std::string& logText = fmt::format("Provided texture slot {} exceeded the max number of texture slots {}", slot, _maxTextureSlots);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
}

void TextureImpl::Set(unsigned int /*unused*/, const TextureData& textureData, unsigned char* pixelData) {
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
    for (unsigned long long i{}; i < textureData.Parameters.size(); ++i) {
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

    glTexImage2D(target, 0, internalFormat, textureData.Width, textureData.Height, 0, textureFormat, textureDataType, pixelData);
    glGenerateMipmap(target);
}

void TextureImpl::Delete(unsigned int& id, ETextureType /*unused*/) {
    glDeleteTextures(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
