#pragma once

#include "DLL_API.h"
#include <vector>

namespace GraphicLib {
struct IndexBufferDataElement {
    unsigned int E1{};
    unsigned int E2{};
    unsigned int E3{};
};

class DLL_API IndexBuffer {
public:
    IndexBuffer() = default;
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = default;
    IndexBuffer& operator=(const IndexBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set(std::vector<IndexBufferDataElement>&& indices);
    void Delete();
    const std::vector<IndexBufferDataElement>& Get() const;

private:
    std::vector<IndexBufferDataElement> _indices{};
    unsigned int _id{};
};
} // namespace GraphicLib
