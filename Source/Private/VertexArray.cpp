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

VertexArray::~VertexArray() {
    Delete();
}

void VertexArray::Initialise() {
    GraphicAPI::Get().GetVertexArrayImpl().Initialise(_id);
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
}

void VertexArray::Bind() {
    GraphicAPI::Get().GetVertexArrayImpl().Bind(_id);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() {
    GraphicAPI::Get().GetVertexArrayImpl().Unbind(_id);
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::Draw() {
    if (_indexBuffer.Get().size() > 0) {
        const unsigned long long trianglesCount = _indexBuffer.Get().size() * 3;
        if (static_cast<long long>(trianglesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
            return;
        }
        GraphicAPI::Get().GetVertexArrayImpl().DrawTriangles(_id, static_cast<int>(trianglesCount));
    }
    else {
        unsigned long long attributesCount{};
        for (unsigned long long i{}; i < _vertexBuffer.GetVertexAttributes().size(); ++i) {
            attributesCount += static_cast<unsigned long long>(_vertexBuffer.GetVertexAttributes()[i]);
        }

        const unsigned long long verticesCount = _vertexBuffer.GetVertexData().size() / attributesCount;
        if (static_cast<long long>(verticesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Vertices count exceeded the max number");
            return;
        }
        GraphicAPI::Get().GetVertexArrayImpl().DrawVertices(_id, static_cast<int>(verticesCount));
    }
}

void VertexArray::Delete() {
    GraphicAPI::Get().GetVertexArrayImpl().Delete(_id);
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    return _vertexBuffer;
}

VertexBuffer& VertexArray::GetVertexBuffer() {
    return _vertexBuffer;
}

const IndexBuffer& VertexArray::GetIndexBuffer() const {
    return _indexBuffer;
}

IndexBuffer& VertexArray::GetIndexBuffer() {
    return _indexBuffer;
}
} // namespace GraphicLib
