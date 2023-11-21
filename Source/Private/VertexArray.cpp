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
    const auto trianglesCount = _indexBuffer.Get().Size() * 3;
    if (trianglesCount > std::numeric_limits<int>::max()) {
       LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
        return;
    }
    GraphicAPI::Get().GetVertexArrayImpl().Draw(_id, static_cast<int>(trianglesCount));
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
