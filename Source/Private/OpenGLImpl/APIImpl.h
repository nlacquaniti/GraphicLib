#pragma once

#include "FrameBufferImpl.h"
#include "IndexBufferImpl.h"
#include "RenderBufferImpl.h"
#include "ShaderImpl.h"
#include "TextureImpl.h"
#include "VertexArrayImpl.h"
#include "VertexBufferImpl.h"

namespace GraphicLib {
namespace OpenGLImpl {
class APIImpl final {
public:
    static const APIImpl& Get();
    const VertexArrayImpl& GetVertexArrayImpl() const;
    const VertexBufferImpl& GetVertexBufferImpl() const;
    const IndexBufferImpl& GetIndexBufferImpl() const;
    const TextureImpl& GetTextureImpl() const;
    const ShaderImpl& GetShaderImpl() const;
    const FrameBufferImpl& GetFrameBufferImpl() const;

private:
    static APIImpl* _instance;
    VertexArrayImpl _vertexArrayImpl{};
    VertexBufferImpl _vertexBufferImpl{};
    IndexBufferImpl _indexBufferImpl{};
    TextureImpl _textureImpl{};
    ShaderImpl _shaderImpl{};
    FrameBufferImpl _frameBufferImpl{};
};
} // namespace OpenGLImpl
} // namespace GraphicLib
