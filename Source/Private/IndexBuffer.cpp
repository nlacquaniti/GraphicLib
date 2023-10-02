#include "GraphicLib/IndexBuffer.h"

#include "InternalLogger.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/IndexBufferOpsImpl.h"
using IndexBufferOpsImpl = GraphicLib::OpenGLImpl::IndexBufferOpsImpl;
#else
#error "No IndexBufferImpl has been detected."
#endif

namespace GraphicLib {
void IndexBufferOps::_initialiseIndexBufferData(unsigned int& id) {
    IndexBufferOpsImpl::InitialiseIndexBufferData(id);
}

void IndexBufferOps::_bind(unsigned int id) {
    IndexBufferOpsImpl::Bind(id);
}

void IndexBufferOps::_unbind(unsigned int id) {
    IndexBufferOpsImpl::Unbind(id);
}

void IndexBufferOps::_setData(unsigned int id, const StackArraySpan<unsigned int>& data) {
    if (data.Count() == 0) {
        InternalLogger::Get().LogInternalError("IndexBufferOps::SetData()", "Empty data");
        return;
    }

    if (data.Count() != data.Size()) {
        InternalLogger::Get().LogInternalError("IndexBufferOps::SetData()", "Not all data have been set");
        return;
    }

    IndexBufferOpsImpl::SetData(id, data);
}
} // namespace GraphicLib
