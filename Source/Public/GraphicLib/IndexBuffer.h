#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <vector>

namespace GraphicLib {
class DLL_API IndexBuffer {
public:
    IndexBuffer() noexcept = default;
    IndexBuffer(IndexBuffer&&) noexcept = default;
    IndexBuffer& operator=(IndexBuffer&&) noexcept = default;
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    ~IndexBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<int>&& indices);
    [[nodiscard]] const std::vector<int>& Get() const;

private:
    std::vector<int> _indices;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
