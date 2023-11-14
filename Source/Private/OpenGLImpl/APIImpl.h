#pragma once

#include "Utilities/Singleton.h"

namespace GraphicLib {
namespace OpenGLImpl {
class APIImpl : public Singleton<APIImpl> {
public:
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
    VertexArrayImpl _vertexArrayImpl;
    VertexBufferImpl _vertexBufferImpl;
    IndexBufferImpl _indexBufferImpl;
    TextureImpl _textureImpl;
    ShaderImpl _shaderImpl;
};
} // namespace OpenGLImpl
} // namespace GraphicLib