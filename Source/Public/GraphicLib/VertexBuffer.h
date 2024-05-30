#pragma once

#include "DLL_API.h"
#include <vector>

namespace GraphicLib {
struct VertexAttribute {
    int Id{};
    int Size{};
};

class DLL_API VertexBuffer {
public:
    VertexBuffer() noexcept;
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    ~VertexBuffer() noexcept;
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<float>&& vertexData, std::vector<VertexAttribute>&& vertexAttributes);
    void Delete();
    [[nodiscard]] const std::vector<float>& GetVertexData() const;
    [[nodiscard]] const std::vector<VertexAttribute>& GetVertexAttributes() const;

private:
    std::vector<float> _vertexData;
    std::vector<VertexAttribute> _vertexAttributes;
    unsigned int _id{};
};
} // namespace GraphicLib
