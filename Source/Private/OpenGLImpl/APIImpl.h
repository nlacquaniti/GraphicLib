#pragma once

#include "IndexBufferImpl.h"
#include "ShaderImpl.h"
#include "TextureImpl.h"
#include "VertexArrayImpl.h"
#include "VertexBufferImpl.h"

namespace GraphicLib {
namespace OpenGLImpl {
class APIImpl final {
public:
    static APIImpl& Get();
    static const APIImpl& ConstGet();

    const VertexArrayImpl& GetVertexArrayImpl() const;
    VertexArrayImpl& GetVertexArrayImpl();

    const VertexBufferImpl& GetVertexBufferImpl() const;
    VertexBufferImpl& GetVertexBufferImpl();

    const IndexBufferImpl& GetIndexBufferImpl() const;
    IndexBufferImpl& GetIndexBufferImpl();

    const TextureImpl& GetTextureImpl() const;
    TextureImpl& GetTextureImpl();

    const ShaderImpl& GetShaderImpl() const;
    ShaderImpl& GetShaderImpl();

private:
    static APIImpl* _instance;
    VertexArrayImpl _vertexArrayImpl;
    VertexBufferImpl _vertexBufferImpl;
    IndexBufferImpl _indexBufferImpl;
    TextureImpl _textureImpl;
    ShaderImpl _shaderImpl;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
