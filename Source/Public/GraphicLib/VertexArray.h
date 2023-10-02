#pragma once

#include "DLL_API.h"
#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
struct VertexArrayData final {
    using VertexBufferDataType = VertexBufferData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT>;
    using IndexBufferDataType = IndexBufferData<INDICES_COUNT>;
    VertexArrayData(const VertexBufferDataType& inVertexBuffer, const IndexBufferDataType& inIndexBuffer);
    VertexBufferDataType vertexBufferData{};
    IndexBufferDataType indexBufferData{};
    unsigned int id{};
};

class VertexArrayOps final {
public:
    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
    static void InitialiseVertexArrayData(VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData);

    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
    static void Bind(const VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData);

    template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
    static void Unbind(const VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData);

private:
    DLL_API static void _initialiseVertexArrayData(unsigned int& id);
    DLL_API static void _bind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId);
    DLL_API static void _unbind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId);
};

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>::VertexArrayData(
    const VertexBufferDataType& inVertexBuffer, const IndexBufferDataType& inIndexBuffer)
    : vertexBufferData(inVertexBuffer)
    , IndexBufferData(inIndexBuffer) {
    VertexArrayOps::InitialiseVertexArrayData(*this);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
void VertexArrayOps::InitialiseVertexArrayData(VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData) {
    _initialiseVertexArrayData(vertexArrayData.id);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
void VertexArrayOps::Bind(const VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData) {
    _bind(vertexArrayData.id, vertexArrayData.vertexBufferData.id, vertexArrayData.indexBufferData.id);
}

template<typename TVertexData, unsigned int ATTRIBUTES_COUNT, unsigned int VERTICES_COUNT, unsigned int INDICES_COUNT>
void VertexArrayOps::Unbind(const VertexArrayData<TVertexData, ATTRIBUTES_COUNT, VERTICES_COUNT, INDICES_COUNT>& vertexArrayData) {
    _unbind(vertexArrayData.id, vertexArrayData.vertexBufferData.id, vertexArrayData.indexBufferData.id);
}

} // namespace GraphicLib
