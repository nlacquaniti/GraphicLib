#include "GraphicLib/FrameBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
FrameBuffer::~FrameBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetFrameBufferImpl().Delete(_id.Value);
}

void FrameBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    GraphicAPI::Get().GetFrameBufferImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void FrameBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetFrameBufferImpl().Bind(_id.Value);
}

void FrameBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetFrameBufferImpl().Unbind(_id.Value);
}

void FrameBuffer::Set() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetFrameBufferImpl().Set(_id.Value, _texture, _renderBuffer);
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
