#pragma once

#include "DLL_API.h"
#include "GraphicLib/Utilities/StackArray.h"

namespace GraphicLib {
struct IndexBufferDataElement {
    unsigned int E1{};
    unsigned int E2{};
    unsigned int E3{};
};

template<unsigned int INDICES_COUNT>
struct IndexBufferData final {
    IndexBufferData();
    StackArray<IndexBufferDataElement, INDICES_COUNT> data{};
    unsigned int id{};
};

class IndexBufferOps final {
public:
    template<unsigned int INDICES_COUNT>
    static void InitialiseIndexBufferData(IndexBufferData<INDICES_COUNT>& indexBufferData);

    template<unsigned int INDICES_COUNT>
    static void Bind(const IndexBufferData<INDICES_COUNT>& indexBufferData);

    template<unsigned int INDICES_COUNT>
    static void Unbind(const IndexBufferData<INDICES_COUNT>& indexBufferData);

    template<unsigned int INDICES_COUNT>
    static void AddData(IndexBufferData<INDICES_COUNT>& indexBufferData, const IndexBufferDataElement& data);

    template<unsigned int INDICES_COUNT>
    static void SendBufferToGPU(const IndexBufferData<INDICES_COUNT>& indexBufferData);

private:
    DLL_API static void _initialiseIndexBufferData(unsigned int& id);
    DLL_API static void _bind(unsigned int id);
    DLL_API static void _unbind(unsigned int id);
    DLL_API static void _sendBufferToGPU(unsigned int id, const StackArraySpan<IndexBufferDataElement>& data);
};

template<unsigned int INDICES_COUNT>
IndexBufferData<INDICES_COUNT>::IndexBufferData() {
    IndexBufferOps::InitialiseIndexBufferData(*this);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::InitialiseIndexBufferData(IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _initialiseIndexBufferData(indexBufferData.id);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::Bind(const IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _bind(indexBufferData.id);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::Unbind(const IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _unbind(indexBufferData.id);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::AddData(IndexBufferData<INDICES_COUNT>& indexBufferData, const IndexBufferDataElement& data) {
    indexBufferData.data.Add(data);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::SendBufferToGPU(const IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _sendBufferToGPU(indexBufferData.id, MakeStackArraySpan(indexBufferData.data));
}

} // namespace GraphicLib
