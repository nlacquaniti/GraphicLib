#pragma once

#include <cassert>

namespace GraphicLib {
template<typename TArrayType, unsigned int ARRAY_SIZE> //
class StackArray final {
public:
    using ArrayType = TArrayType;
    void Add(const TArrayType& element) {
        if (_dataAllocated < ARRAY_SIZE) {
            _data[_dataAllocated++] = element;
        }
    }
    constexpr unsigned int GetSize() const { return ARRAY_SIZE; }
    unsigned int GetCount() const { return _dataAllocated; }
    bool IsFull() const { return _dataAllocated == ARRAY_SIZE; }
    const TArrayType* GetData() const { return &_data[0]; }
    TArrayType* GetData() { return &_data[0]; }

private:
    TArrayType _data[ARRAY_SIZE];
    unsigned int _dataAllocated{};
};

template<typename TArrayType>
class StackArraySpan final {
public:
    using ArrayType = TArrayType;

    StackArraySpan(const TArrayType* data, unsigned int dataAllocated, unsigned int dataSize)
        : _data(data)
        , _dataAllocated(dataAllocated)
        , _dataSize(dataSize) {}

    const ArrayType& operator[](unsigned int index) const {
        assert(_data != nullptr);
        assert(index <= _dataAllocated);
        return _data[index];
    }
    const TArrayType* Data() const { return _data; }
    unsigned int Count() const { return _dataAllocated; }
    unsigned int Size() const { return _dataSize; }
    bool IsFull() const { return _dataSize != _dataAllocated; }

private:
    const TArrayType* _data{};
    const unsigned int _dataAllocated{};
    const unsigned int _dataSize{};
};

template<typename TArrayType, unsigned int ARRAY_SIZE>
StackArraySpan<TArrayType> MakeStackArraySpan(const StackArray<TArrayType, ARRAY_SIZE>& stackArray) {
    return {stackArray.GetData(), stackArray.GetCount(), ARRAY_SIZE};
}

template<typename TSpanArrayType, typename TArrayType, unsigned int ARRAY_SIZE>
StackArraySpan<TSpanArrayType> MakeStackArraySpan(const StackArray<TArrayType, ARRAY_SIZE>& stackArray) {
    return {(const TSpanArrayType*)stackArray.GetData(), stackArray.GetCount(), ARRAY_SIZE};
}

} // namespace GraphicLib
