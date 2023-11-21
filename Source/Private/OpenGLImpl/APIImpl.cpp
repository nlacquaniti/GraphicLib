#include "OpenGLImpl/APIImpl.h"

#include "InternalLogger.h"
#include <glad/glad.h>
#include "OpenGLImpl/OpenGLLogSystem.h"
#include <memory>

namespace GraphicLib {
namespace OpenGLImpl {
APIImpl* APIImpl::_instance{};

APIImpl& APIImpl::Get() {
    if (_instance == nullptr) {
        gladLoadGL();
        InternalLogger::Get().AttachExternalLogSystem(std::make_unique<OpenGLLogSystem>());
        _instance = new APIImpl{};
    }

    return *_instance;
}

const APIImpl& APIImpl::ConstGet() {
    return Get();
}

const VertexArrayImpl& APIImpl::GetVertexArrayImpl() const {
    return _vertexArrayImpl;
}

VertexArrayImpl& APIImpl::GetVertexArrayImpl() {
    return _vertexArrayImpl;
}

const VertexBufferImpl& APIImpl::GetVertexBufferImpl() const {
    return _vertexBufferImpl;
}

VertexBufferImpl& APIImpl::GetVertexBufferImpl() {
    return _vertexBufferImpl;
}

const IndexBufferImpl& APIImpl::GetIndexBufferImpl() const {
    return _indexBufferImpl;
}

IndexBufferImpl& APIImpl::GetIndexBufferImpl() {
    return _indexBufferImpl;
}

const TextureImpl& APIImpl::GetTextureImpl() const {
    return _textureImpl;
}

TextureImpl& APIImpl::GetTextureImpl() {
    return _textureImpl;
}

const ShaderImpl& APIImpl::GetShaderImpl() const {
    return _shaderImpl;
}

ShaderImpl& APIImpl::GetShaderImpl() {
    return _shaderImpl;
}
} // namespace OpenGLImpl
} // namespace GraphicLib
