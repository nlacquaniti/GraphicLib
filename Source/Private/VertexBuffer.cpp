#include "GraphicLib/VertexBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

#include <format>

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

void VertexBuffer::Set(std::vector<float>&& vertexData, const std::span<const VertexAttribute>& vertexAttributes) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (vertexData.empty()) {
        LOG_INTERNAL_ERROR("Vertex data is empty");
        return;
    }

    if (vertexAttributes.empty()) {
        LOG_INTERNAL_ERROR("Vertex attributes are Empty");
        return;
    }

    if (vertexAttributes.size() > MAX_VERTEX_ATTRIBUTES_SIZE) {
        LOG_INTERNAL_ERROR("Vertex attributes size is greater then MAX_VERTEX_ATTRIBUTES_SIZE");
        return;
    }

    for (size_t i{}; i < vertexAttributes.size(); ++i) {
        const VertexAttribute& vertexAttribute = vertexAttributes[i];
        if (vertexAttribute.Name[0] == '\0') {
            const std::string logText = std::format("VertexAttribute name at index {} is empty", i);
            LOG_INTERNAL_ERROR(logText.c_str());
        }

        if (vertexAttribute.Count == 0) {
            const std::string logText = std::format("VertexAttribute {} Count at index {} is 0", vertexAttribute.Name.data(), i);
            LOG_INTERNAL_ERROR(logText.c_str());
        }
        _vertexAttributes.at(i) = vertexAttribute;
    }

    _vertexAttributesCount = vertexAttributes.size();
    _vertexData = std::move(vertexData);

    Bind();
    GraphicAPI::Get().GetVertexBufferImpl().Set(_id.Value, _vertexData, vertexAttributes);
    Unbind();
}

std::span<const VertexAttribute> VertexBuffer::GetVertexAttributes() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return {_vertexAttributes.data(), _vertexAttributesCount};
}

const std::vector<float>& VertexBuffer::GetVertexData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexData;
}
} // namespace GraphicLib
