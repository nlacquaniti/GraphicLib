#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <array>
#include <vector>

namespace GraphicLib {
struct VertexAttribute {
    std::array<char, 24> Name;
    int Count;
};

struct VertexBufferData {
    std::vector<float> VertexData;
    std::vector<VertexAttribute> vertexAttributes;
};

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
    void Set(VertexBufferData&& data);
    [[nodiscard]] const VertexBufferData& GetData() const;

private:
    VertexBufferData _data;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
