#include "GraphicLib/VertexBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
VertexBuffer::~VertexBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetVertexBufferImpl().Delete(_id.Value);
}

void VertexBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    GraphicAPI::Get().GetVertexBufferImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void VertexBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetVertexBufferImpl().Bind(_id.Value);
}

void VertexBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetVertexBufferImpl().Unbind(_id.Value);
}

void VertexBuffer::Set(VertexBufferData&& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (data.VertexData.empty()) {
        LOG_INTERNAL_ERROR("Vertex data is empty");
        return;
    }

    if (data.vertexAttributes.empty()) {
        LOG_INTERNAL_ERROR("Vertex attributes are Empty");
        return;
    }

    _data = std::move(data);
    Bind();
    GraphicAPI::Get().GetVertexBufferImpl().Set(_id.Value, _data);
    Unbind();
}

const VertexBufferData& VertexBuffer::GetData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _data;
}
} // namespace GraphicLib
