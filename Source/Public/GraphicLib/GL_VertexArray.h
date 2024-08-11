#pragma once

#include "GraphicLib/Storage.h"

#include <array>
#include <vector>

namespace GraphicLib {
using VertexArrayId = std::size_t;

struct VertexAttribute {
    static constexpr std::size_t MAX_NAME_SIZE = 24;
    std::array<char, MAX_NAME_SIZE> Name;
    int Count;
};

struct VertexBuffer {
    static constexpr std::size_t ATTRIBUTES_MAX_SIZE = 16;
    std::array<VertexAttribute, ATTRIBUTES_MAX_SIZE> VertexAttributes;
    std::vector<float> VertexData;
    size_t VertexAttributesCount;
};

struct IndexBuffer {
    std::vector<unsigned int> Indices;
};

VertexArrayId CreateVertexArray(
    const VertexBuffer& vertexBuffer,
    const IndexBuffer& indexBuffer);
} // namespace GraphicLib