#include "GraphicLib/IndexBuffer.h"

#include "InternalLogger.h"

#include "OpenGLImpl/IndexBufferImpl.h"

namespace GraphicLib {
IndexBuffer::~IndexBuffer() noexcept {
    if (!_id.IsInitialised) {
        return;
    }

    Internal::DeleteIndexBuffer(&_id.Value);
}

void IndexBuffer::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    Internal::InitialiseIndexBuffer(&_id.Value);
    _id.IsInitialised = true;
}

void IndexBuffer::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::BindIndexBuffer(_id.Value);
}

void IndexBuffer::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::UnbindIndexBuffer();
}

void IndexBuffer::Set(std::vector<unsigned int>&& indices) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (indices.empty()) {
        LOG_INTERNAL_ERROR("Indicies are empty");
        return;
    }

    _indices = std::move(indices);
    Bind();
    Internal::SetIndexBuffer(_indices.data(), _indices.size());
    Unbind();
}

const std::vector<unsigned int>& IndexBuffer::GetIndices() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    
    return _indices;
}
} // namespace GraphicLib
