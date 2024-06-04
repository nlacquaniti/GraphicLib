#include "GraphicLib/IndexBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
IndexBuffer::~IndexBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetIndexBufferImpl().Delete(_id.Value);
}

void IndexBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    GraphicAPI::Get().GetIndexBufferImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void IndexBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetIndexBufferImpl().Bind(_id.Value);
}

void IndexBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetIndexBufferImpl().Unbind(_id.Value);
}

void IndexBuffer::Set(std::vector<IndexBufferDataElement>&& indices) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    _indices = std::move(indices);
    Bind();
    GraphicAPI::Get().GetIndexBufferImpl().Set(_id.Value, _indices);
}

const std::vector<IndexBufferDataElement>& IndexBuffer::Get() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _indices;
}
} // namespace GraphicLib
