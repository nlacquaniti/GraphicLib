#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <vector>

namespace GraphicLib {
struct IndexBufferDataElement {
    unsigned int E1{};
    unsigned int E2{};
    unsigned int E3{};
};

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
    void Set(std::vector<IndexBufferDataElement>&& indices);
    [[nodiscard]] const std::vector<IndexBufferDataElement>& Get() const;

private:
    std::vector<IndexBufferDataElement> _indices;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
