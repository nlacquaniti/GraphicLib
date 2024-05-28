#pragma once

#include "DLL_API.h"
#include <vector>

namespace GraphicLib {
class DLL_API IndexBuffer {
public:
    IndexBuffer() = default;
    IndexBuffer(IndexBuffer&&) = default;
    IndexBuffer& operator=(IndexBuffer&&) = default;
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    ~IndexBuffer();
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<int>&& indices);
    void Delete();
    [[nodiscard]] const std::vector<int>& Get() const;

private:
    std::vector<int> _indices;
    unsigned int _id{};
};
} // namespace GraphicLib
