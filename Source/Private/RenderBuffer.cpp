#include "GraphicLib/RenderBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
RenderBuffer::~RenderBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetRenderBufferImpl().Delete(_id.Value);
}

void RenderBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already Initialised");
        return;
    }
    GraphicAPI::Get().GetRenderBufferImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void RenderBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetRenderBufferImpl().Bind(_id.Value);
}

void RenderBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetRenderBufferImpl().Unbind(_id.Value);
}

void RenderBuffer::Set(const RenderBufferData& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    _data = data;
    Bind();
    GraphicAPI::Get().GetRenderBufferImpl().Set(_id.Value, data);
}

unsigned int RenderBuffer::GetID() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _id.Value;
}

const RenderBufferData& RenderBuffer::GetData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _data;
}

} // namespace GraphicLib
