#pragma once

#include "DLL_API.h"
#include "GraphicLib/Utilities/StackArray.h"

namespace GraphicLib {
template<unsigned int INDICES_COUNT>
struct IndexBufferData final {
    IndexBufferData();
    StackArray<unsigned int, INDICES_COUNT> data{};
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
    static void SetData(const IndexBufferData<INDICES_COUNT>& indexBufferData);

private:
    DLL_API static void _initialiseIndexBufferData(unsigned int& id);
    DLL_API static void _bind(unsigned int id);
    DLL_API static void _unbind(unsigned int id);
    DLL_API static void _setData(unsigned int id, const StackArraySpan<unsigned int>& data);
};

template<unsigned int INDICES_COUNT>
IndexBufferData<INDICES_COUNT>::IndexBufferData() {
    IndexBufferOps::InitialiseIndexBufferData(*this);
}

template<unsigned int INDICES_COUNT>
void IndexBufferOps::InitialiseIndexBufferData(IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _initialiseIndexBufferData(IndexBufferData.id)
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
void IndexBufferOps::SetData(const IndexBufferData<INDICES_COUNT>& indexBufferData) {
    _setData(MakeStackArraySpan(indexBufferData));
}

} // namespace GraphicLib
