#include "GraphicLib/VertexArray.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include "InternalLogger.h"
#include <limits>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {

VertexArray::~VertexArray() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetVertexArrayImpl().Delete(_id.Value);
}

void VertexArray::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    GraphicAPI::Get().GetVertexArrayImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
}

void VertexArray::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetVertexArrayImpl().Bind(_id.Value);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetVertexArrayImpl().Unbind(_id.Value);
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::Set(VertexBufferData&& vertexBufferData) {
    Bind();
    _vertexBuffer.Set(std::move(vertexBufferData));
    Unbind();
}

void VertexArray::Set(VertexBufferData&& vertexBufferData, IndexBufferData&& indexBufferData) {
    Bind();
    _vertexBuffer.Set(std::move(vertexBufferData));
    _indexBuffer.Set(std::move(indexBufferData));
    Unbind();
}

void VertexArray::Draw() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (!_indexBuffer.GetData().Indicies.empty()) {
        const unsigned long long trianglesCount = _indexBuffer.GetData().Indicies.size() * 3;
        if (static_cast<long long>(trianglesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
            return;
        }

        Bind();
        GraphicAPI::Get().GetVertexArrayImpl().DrawTriangles(_id.Value, static_cast<int>(trianglesCount));
        Unbind();
    } else if (!_vertexBuffer.GetData().VertexData.empty() && !_vertexBuffer.GetData().vertexAttributes.empty()) {
        unsigned long long attributesCount{};
        for (const VertexAttribute& vertexAttribute : _vertexBuffer.GetData().vertexAttributes) {
            attributesCount += static_cast<unsigned long long>(vertexAttribute.Count);
        }

        const unsigned long long verticesCount = _vertexBuffer.GetData().VertexData.size() / attributesCount;
        if (static_cast<long long>(verticesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Vertices count exceeded the max number");
            return;
        }

        Bind();
        GraphicAPI::Get().GetVertexArrayImpl().DrawVertices(_id.Value, static_cast<int>(verticesCount));
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
