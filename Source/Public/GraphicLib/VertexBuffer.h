#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <vector>

namespace GraphicLib {
struct VertexAttribute {
    int Id{};
    int Size{};
};

class DLL_API VertexBuffer {
public:
    VertexBuffer() = default;
    VertexBuffer(VertexBuffer&&) noexcept = default;
    VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    ~VertexBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<float>&& vertexData, std::vector<VertexAttribute>&& vertexAttributes);
    [[nodiscard]] const std::vector<float>& GetVertexData() const;
    [[nodiscard]] const std::vector<VertexAttribute>& GetVertexAttributes() const;

private:
    std::vector<float> _vertexData;
    std::vector<VertexAttribute> _vertexAttributes;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
