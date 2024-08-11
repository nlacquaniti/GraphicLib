#include "GraphicLib/VertexArray.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include "InternalLogger.h"

#include "OpenGLImpl/VertexArrayImpl.h"

#include <limits>

namespace GraphicLib {
VertexArray::~VertexArray() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    Internal::DeleteVertexArray(&_id.Value);
}

void VertexArray::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    Internal::InitialiseVertexArray(&_id.Value);
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
    _id.IsInitialised = true;
}

void VertexArray::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    Internal::BindVertexArray(_id.Value);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    Internal::UnbindVertexArray();
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::SetVertexBuffer(std::vector<float>&& vertexData,
    const std::span<const VertexAttribute>& vertexAttributes) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    Bind();
    _vertexBuffer.Set(std::move(vertexData), vertexAttributes);
    Unbind();
}

void VertexArray::SetIndexBuffer(std::vector<unsigned int>&& indices) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    Bind();
    _indexBuffer.Set(std::move(indices));
    Unbind();
}

void VertexArray::Draw() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (!_indexBuffer.GetIndices().empty()) {
        const std::size_t trianglesCount = _indexBuffer.GetIndices().size() * 3;
        if (static_cast<long long>(trianglesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
            return;
        }

        Bind();
        Internal::DrawTrianglesVertexArray(static_cast<int>(trianglesCount));
        Unbind();
    } else if (!_vertexBuffer.GetVertexData().empty() &&
               !_vertexBuffer.GetVertexAttributes().empty()) {
        unsigned long long attributesCount{};
        for (const VertexAttribute& vertexAttribute :
            _vertexBuffer.GetVertexAttributes()) {
            attributesCount += static_cast<unsigned long long>(vertexAttribute.Count);
        }

        const std::size_t verticesCount =
            _vertexBuffer.GetVertexData().size() / attributesCount;
        if (static_cast<long long>(verticesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Vertices count exceeded the max number");
            return;
        }

        Bind();
        Internal::DrawVerticesVertexArray(static_cast<int>(verticesCount));
        Unbind();
    } else {
        LOG_INTERNAL_ERROR("Draw failed, both IndexBuffer and VertexBuffer are empty");
    }
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexBuffer;
}

const IndexBuffer& VertexArray::GetIndexBuffer() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _indexBuffer;
}
} // namespace GraphicLib
