#include "OpenGLImpl/APIImpl.h"

#include "InternalLogger.h"
#include "OpenGLImpl/OpenGLLogSystem.h"
#include <glad/glad.h>
#include <memory>

namespace GraphicLib::OpenGLImpl {
APIImpl* APIImpl::_instance{};

const APIImpl& APIImpl::Get() {
    if (_instance == nullptr) {
        gladLoadGL();
        InternalLogger::Get().AttachExternalLogSystem(std::make_unique<OpenGLLogSystem>());
        _instance = new APIImpl{};
    }

    return *_instance;
}

const VertexArrayImpl& APIImpl::GetVertexArrayImpl() const {
    return _vertexArrayImpl;
}

const VertexBufferImpl& APIImpl::GetVertexBufferImpl() const {
    return _vertexBufferImpl;
}

const IndexBufferImpl& APIImpl::GetIndexBufferImpl() const {
    return _indexBufferImpl;
}

const TextureImpl& APIImpl::GetTextureImpl() const {
    return _textureImpl;
}

const ShaderImpl& APIImpl::GetShaderImpl() const {
    return _shaderImpl;
}

const FrameBufferImpl& APIImpl::GetFrameBufferImpl() const {
    return _frameBufferImpl;
}

const RenderBufferImpl& APIImpl::GetRenderBufferImpl() const {
    return _renderBufferImpl;
}
} // namespace GraphicLib::OpenGLImpl
