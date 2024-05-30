#include "GraphicLib/FrameBuffer.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
FrameBuffer::FrameBuffer() noexcept {
    GraphicAPI::Get().GetFrameBufferImpl().Initialise(_id);
}

FrameBuffer::~FrameBuffer() noexcept {
    Delete();
}

void FrameBuffer::Bind() const {
    GraphicAPI::Get().GetFrameBufferImpl().Bind(_id);
}

void FrameBuffer::Unbind() const {
    GraphicAPI::Get().GetFrameBufferImpl().Unbind(_id);
}

void FrameBuffer::Set() {
    GraphicAPI::Get().GetFrameBufferImpl().Set(_id, _texture, _renderBuffer);
}

void FrameBuffer::Delete() {
    GraphicAPI::Get().GetFrameBufferImpl().Delete(_id);
}

const Texture& FrameBuffer::GetTexture() const {
    return _texture;
}

Texture& FrameBuffer::GetTexture() {
    return _texture;
}

const RenderBuffer& FrameBuffer::GetRenderBuffer() const {
    return _renderBuffer;
}

RenderBuffer& FrameBuffer::GetRenderBuffer() {
    return _renderBuffer;
}
} // namespace GraphicLib
