#pragma once

#include "DLL_API.h"
#include "GraphicLib/Utilities/StackArray.h"

namespace GraphicLib {
template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
struct VertexBufferData final {
    VertexBufferData();
    StackArray<unsigned int, ATTRIBUTES_COUNT> attributes{};
    StackArray<TVertexData, VERTICES_COUNT> data{};
    unsigned int id{};
};

class VertexBufferOps final {
public:
    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
    static void InitialiseVertexBufferData(VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData);

    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
    static void Bind(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData);

    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
    static void Unbind(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData);

    template<typename TVertexBufferAttribute, typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
    static void AddAttribute(VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData);

    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
    static void SetData(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData);

private:
    DLL_API static void _initialiseVertexBufferData(unsigned int& id);
    DLL_API static void _bind(unsigned int id);
    DLL_API static void _unbind(unsigned int id);
    DLL_API static void _setData(unsigned int id, const StackArraySpan<unsigned int>& attributes, const StackArraySpan<float>& data);
};

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>::VertexBufferData() {
    VertexBufferOps::InitialiseVertexBufferData(*this);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
void VertexBufferOps::InitialiseVertexBufferData(VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData) {
    _initialiseVertexBufferData(vertexBufferData.id);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
void VertexBufferOps::Bind(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData) {
    _bind(vertexBufferData.id);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
void VertexBufferOps::Unbind(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData) {
    _unbind(vertexBufferData.id);
}

template<typename TVertexBufferAttribute, typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
void VertexBufferOps::AddAttribute(VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData) {
    static_assert(sizeof(TVertexBufferAttribute) % sizeof(float) == 0);
    constexpr unsigned int attributeElementsCount = sizeof(TVertexBufferAttribute) / sizeof(float);
    vertexBufferData.attributes.Add(attributeElementsCount);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT>
void VertexBufferOps::SetData(const VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>& vertexBufferData) {
    _setData(                                                          //
        vertexBufferData.id,                                           //
        MakeStackArraySpan<unsigned int>(vertexBufferData.attributes), //
        MakeStackArraySpan<float>(vertexBufferData.data)               //
    );
}
} // namespace GraphicLib
