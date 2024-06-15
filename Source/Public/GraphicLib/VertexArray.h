#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
class DLL_API VertexArray {
public:
    VertexArray() noexcept = default;
    VertexArray(VertexArray&&) noexcept = default;
    VertexArray& operator=(VertexArray&&) noexcept = default;
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    ~VertexArray() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void SetVertexBuffer(std::vector<float>&& vertexData, const std::span<const VertexAttribute>& vertexAttributes);
    void SetIndexBuffer(std::vector<unsigned int>&& Indicies);
    void Draw();
    [[nodiscard]] const VertexBuffer& GetVertexBuffer() const;
    [[nodiscard]] const IndexBuffer& GetIndexBuffer() const;

private:
    VertexBuffer _vertexBuffer;
    IndexBuffer _indexBuffer;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
