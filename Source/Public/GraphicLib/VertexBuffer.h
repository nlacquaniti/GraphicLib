#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <array>
#include <span>
#include <vector>

namespace GraphicLib {
struct VertexAttribute {
    static constexpr std::size_t MAX_NAME_SIZE = 24;
    std::array<char, MAX_NAME_SIZE> Name{};
    int Count{};
};

class DLL_API VertexBuffer {
public:
    static constexpr std::size_t MAX_VERTEX_ATTRIBUTES_SIZE = 16;
    VertexBuffer() noexcept = default;
    VertexBuffer(VertexBuffer&&) noexcept = default;
    VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    ~VertexBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<float>&& vertexData, const std::span<const VertexAttribute>& vertexAttributes);
    [[nodiscard]] std::span<const VertexAttribute> GetVertexAttributes() const;
    [[nodiscard]] const std::vector<float>& GetVertexData() const;

private:
    std::array<VertexAttribute, MAX_VERTEX_ATTRIBUTES_SIZE> _vertexAttributes;
    std::vector<float> _vertexData;
    UniqueIdentifier _id;
    std::size_t _vertexAttributesCount{};
};
} // namespace GraphicLib
