#pragma once

#include "FrameBufferImpl.h"
#include "IndexBufferImpl.h"
#include "RenderBufferImpl.h"
#include "ShaderImpl.h"
#include "TextureImpl.h"
#include "VertexArrayImpl.h"
#include "VertexBufferImpl.h"

namespace GraphicLib::OpenGLImpl {
class APIImpl {
public:
    static const APIImpl& Get();
    const VertexArrayImpl& GetVertexArrayImpl() const;
    const IndexBufferImpl& GetIndexBufferImpl() const;
    const TextureImpl& GetTextureImpl() const;
    const ShaderImpl& GetShaderImpl() const;
    const FrameBufferImpl& GetFrameBufferImpl() const;
    const RenderBufferImpl& GetRenderBufferImpl() const;

private:
    static APIImpl* _instance;
    VertexArrayImpl _vertexArrayImpl{};
    IndexBufferImpl _indexBufferImpl{};
    TextureImpl _textureImpl{};
    ShaderImpl _shaderImpl{};
    FrameBufferImpl _frameBufferImpl{};
    RenderBufferImpl _renderBufferImpl{};
};
} // namespace GraphicLib::OpenGLImpl
