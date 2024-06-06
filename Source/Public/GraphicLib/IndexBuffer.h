#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <vector>

namespace GraphicLib {
struct IndexBufferDataElement {
    unsigned int FirstVertex{};
    unsigned int SecondVertex{};
    unsigned int ThirdVertex{};
};

struct IndexBufferData {
    std::vector<IndexBufferDataElement> Indicies;
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
    void Set(IndexBufferData&& data);
    [[nodiscard]] const IndexBufferData& GetData() const;

private:
    IndexBufferData _data;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
