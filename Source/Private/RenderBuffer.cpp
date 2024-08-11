#include "GraphicLib/RenderBuffer.h"

#include "InternalLogger.h"

#include "OpenGLImpl/RenderBufferImpl.h"
#include "OpenGLImpl/Utils/RenderBufferImplUtils.h"

namespace GraphicLib {
RenderBuffer::~RenderBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    Internal::DeleteRenderBuffer(&_id.Value);
}

void RenderBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    Internal::InitialiseRenderBuffer(&_id.Value);
    _id.IsInitialised = true;
}

void RenderBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    Internal::BindRenderBuffer(_id.Value);
}

void RenderBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    Internal::UnbindRenderBuffer();
}

void RenderBuffer::Set(const RenderBufferData& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    unsigned int outOpenGLRenderBufferFormat;
    if (!Internal::ConvertRenderBufferFormatToInternalFormat(
            data.Format, outOpenGLRenderBufferFormat)) {
        return;
    }

    _data = data;
    Bind();
    Internal::SetRenderBuffer(outOpenGLRenderBufferFormat, data.Width, data.Height);
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
