#include "GraphicLib/RenderBuffer.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
RenderBuffer::~RenderBuffer() {
    Delete();
}

void RenderBuffer::Initialise() {
    GraphicAPI::Get().GetRenderBufferImpl().Initialise(_id);
}

void RenderBuffer::Bind() {
    GraphicAPI::Get().GetRenderBufferImpl().Bind(_id);
}

void RenderBuffer::Unbind() {
    GraphicAPI::Get().GetRenderBufferImpl().Unbind(_id);
}

void RenderBuffer::Set(const RenderBufferData& data) {
    _data = data;
    Bind();
    GraphicAPI::Get().GetRenderBufferImpl().Set(_id, data);
}

void RenderBuffer::Delete() {
    GraphicAPI::Get().GetRenderBufferImpl().Delete(_id);
}

unsigned int RenderBuffer::GetID() const {
    return _id;
}

const RenderBufferData& RenderBuffer::GetData() const {
    return _data;
}

} // namespace GraphicLib
