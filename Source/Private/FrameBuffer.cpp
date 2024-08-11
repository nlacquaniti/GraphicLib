#include "GraphicLib/FrameBuffer.h"

#include "GraphicLib/RenderBuffer.h"
#include "InternalLogger.h"

#include "OpenGLImpl/FrameBufferImpl.h"
#include "OpenGLImpl/Utils/RenderBufferImplUtils.h"
#include "OpenGLImpl/Utils/TextureImplUtils.h"

namespace GraphicLib {
FrameBuffer::~FrameBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }

    Internal::DeleteFrameBuffer(&_id.Value);
}

void FrameBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    Internal::InitialiseFrameBuffer(&_id.Value);
    _id.IsInitialised = true;
}

void FrameBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::BindFrameBuffer(_id.Value);
}

void FrameBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::UnbindFrameBuffer();
}

void FrameBuffer::Set() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    unsigned int frameBufferAttachment{};
    if (!Internal::ConvertTextureFormatToFrameBufferAttachment(
            _texture.GetData().Format, frameBufferAttachment)) {
        return;
    }

    unsigned int internalTextureType;
    if (!Internal::ConvertTextureType(_texture.GetData().Type, internalTextureType)) {
        return;
    }

    unsigned int renderBufferAttachment{};
    if (!Internal::ConvertRenderBufferFormatToFrameBufferAttachment(
            _renderBuffer.GetData().Format, renderBufferAttachment)) {
        return;
    }

    if (!Internal::SetFrameBuffer(_texture.GetID(), frameBufferAttachment,
            internalTextureType, _renderBuffer.GetID(), renderBufferAttachment)) {
        LOG_INTERNAL_ERROR("Internal::SetFrameBuffer failed.");
    }
}

const Texture& FrameBuffer::GetTexture() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }

    return _texture;
}

Texture& FrameBuffer::GetTexture() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }

    return _texture;
}

const RenderBuffer& FrameBuffer::GetRenderBuffer() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }

    return _renderBuffer;
}

RenderBuffer& FrameBuffer::GetRenderBuffer() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }

    return _renderBuffer;
}
} // namespace GraphicLib
