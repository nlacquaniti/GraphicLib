#include "GraphicLib/VertexBuffer.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
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

void VertexBuffer::Set(std::vector<float>&& vertexData, std::vector<VertexAttribute>&& vertexAttributes) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    _vertexData = std::move(vertexData);
    _vertexAttributes = std::move(vertexAttributes);
    Bind();
    GraphicAPI::Get().GetVertexBufferImpl().Set(_id.Value, _vertexData, _vertexAttributes);
}

const std::vector<float>& VertexBuffer::GetVertexData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexData;
}

const std::vector<VertexAttribute>& VertexBuffer::GetVertexAttributes() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexAttributes;
}
} // namespace GraphicLib
