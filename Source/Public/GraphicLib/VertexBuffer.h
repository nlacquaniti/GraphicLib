#pragma once

#include "DLL_API.h"
#include <vector>

namespace GraphicLib {
class DLL_API VertexBuffer {
public:
    VertexBuffer() = default;
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = default;
    VertexBuffer& operator=(const VertexBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set(std::vector<float>&& vertexData, std::vector<int>&& vertexAttributes);
    void Delete();
    const std::vector<float>& GetVertexData() const;
    const std::vector<int>& GetVertexAttributes() const;

private:
    std::vector<float> _vertexData{};
    std::vector<int> _vertexAttributes{};
    unsigned int _id{};
};
} // namespace GraphicLib
