#include "GraphicLib/VertexBuffer.h"

#include "InternalLogger.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexBufferOpsImpl.h"
using VertexBufferOpsImpl = GraphicLib::OpenGLImpl::VertexBufferOpsImpl;
#else
#error "No VertexBufferImpl has been detected."
#endif

namespace GraphicLib {
void VertexBufferOps::_initialiseVertexBufferData(unsigned int& id) {
    VertexBufferOpsImpl::InitialiseVertexBufferData(id);
}

void VertexBufferOps::_bind(unsigned int id) {
    VertexBufferOpsImpl::Bind(id);
}

void VertexBufferOps::_unbind(unsigned int id) {
    VertexBufferOpsImpl::Unbind(id);
}

void VertexBufferOps::_setData(unsigned int id, const StackArraySpan<unsigned int>& attributes, const StackArraySpan<float>& data) {
    if (attributes.Count() == 0) {
        InternalLogger::Get().LogInternalError("VertexBufferOps::SetData()", "Empty attributes");
        return;
    }

    if (attributes.Count() != attributes.Size()) {
        InternalLogger::Get().LogInternalError("VertexBufferOps::SetData()", "Not all attributes have been set");
        return;
    }

    if (data.Count() == 0) {
        InternalLogger::Get().LogInternalError("VertexBufferOps::SetData()", "Empty data");
        return;
    }

    if (data.Count() != data.Size()) {
        InternalLogger::Get().LogInternalError("VertexBufferOps::SetData()", "Not all data have been set");
        return;
    }

    VertexBufferOpsImpl::SetData(id, attributes, data);
}
} // namespace GraphicLib
