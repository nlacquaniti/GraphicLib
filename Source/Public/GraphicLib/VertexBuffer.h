#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <vector>

namespace GraphicLib {
class DLL_API VertexBuffer {
public:
    VertexBuffer() noexcept = default;
    VertexBuffer(VertexBuffer&&) noexcept = default;
    VertexBuffer& operator=(VertexBuffer&&) noexcept = default;
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    ~VertexBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<float>&& vertexData, std::vector<int>&& vertexAttributes);
    [[nodiscard]] const std::vector<float>& GetVertexData() const;
    [[nodiscard]] const std::vector<int>& GetVertexAttributes() const;

private:
    std::vector<float> _vertexData;
    std::vector<int> _vertexAttributes;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
