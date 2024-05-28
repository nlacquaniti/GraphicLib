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
    [[nodiscard]] const VertexArrayImpl& GetVertexArrayImpl() const;
    [[nodiscard]] const VertexBufferImpl& GetVertexBufferImpl() const;
    [[nodiscard]] const IndexBufferImpl& GetIndexBufferImpl() const;
    [[nodiscard]] const TextureImpl& GetTextureImpl() const;
    [[nodiscard]] const ShaderImpl& GetShaderImpl() const;
    [[nodiscard]] const FrameBufferImpl& GetFrameBufferImpl() const;
    [[nodiscard]] const RenderBufferImpl& GetRenderBufferImpl() const;

private:
    explicit APIImpl() = default;
    static APIImpl* _instance;
    VertexArrayImpl _vertexArrayImpl{};
    VertexBufferImpl _vertexBufferImpl{};
    IndexBufferImpl _indexBufferImpl{};
    TextureImpl _textureImpl{};
    ShaderImpl _shaderImpl{};
    FrameBufferImpl _frameBufferImpl{};
    RenderBufferImpl _renderBufferImpl{};
};
} // namespace GraphicLib::OpenGLImpl
