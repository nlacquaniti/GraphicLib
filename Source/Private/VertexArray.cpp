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
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
    GraphicAPI::Get().GetVertexArrayImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void VertexArray::Bind() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    GraphicAPI::Get().GetVertexArrayImpl().Bind(_id.Value);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    GraphicAPI::Get().GetVertexArrayImpl().Unbind(_id.Value);
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::Draw() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (_indexBuffer.Get().size() > 0) {
        const unsigned long long trianglesCount = _indexBuffer.Get().size() * 3;
        if (static_cast<long long>(trianglesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
            return;
        }
        GraphicAPI::Get().GetVertexArrayImpl().DrawTriangles(_id.Value, static_cast<int>(trianglesCount));
    } else {
        unsigned long long attributesCount{};
        for (unsigned long long i{}; i < _vertexBuffer.GetVertexAttributes().size(); ++i) {
            attributesCount += static_cast<unsigned long long>(_vertexBuffer.GetVertexAttributes()[i].Size);
        }

        const unsigned long long verticesCount = _vertexBuffer.GetVertexData().size() / attributesCount;
        if (static_cast<long long>(verticesCount) > std::numeric_limits<int>::max()) {
            LOG_INTERNAL_ERROR("Vertices count exceeded the max number");
            return;
        }
        GraphicAPI::Get().GetVertexArrayImpl().DrawVertices(_id.Value, static_cast<int>(verticesCount));
    }
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexBuffer;
}

VertexBuffer& VertexArray::GetVertexBuffer() {
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

IndexBuffer& VertexArray::GetIndexBuffer() {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _indexBuffer;
}
} // namespace GraphicLib
