#pragma once

#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
template<typename TArrayType>
class Array final {
public:
    using SizeType = unsigned long long;

    // Member Functions
    explicit Array() noexcept = default;
    Array(const Array& other) {
        _copy(other);
    }
    Array& operator=(const Array& other) {
        _delete();
        _copy(other);
        return *this;
    }
    ~Array() {
        _delete();
    }

    // Element Access
    TArrayType& operator[](SizeType pos) { return _data[pos]; }
    const TArrayType& operator[](SizeType pos) const { return _data[pos]; }

    TArrayType& Front() { return *_data; }
    const TArrayType& Front() const { return *_data; }

    TArrayType& Back() { return *_data[_usedSize == 0 ? 0 : _usedSize - 1]; }
    const TArrayType& Back() const { return *_data[_usedSize == 0 ? 0 : _usedSize - 1]; }

    TArrayType* Data() noexcept { return _data; }
    const TArrayType* Data() const noexcept { return _data; }

    // Capacity
    bool IsEmpty() const noexcept { return _usedSize == 0; }
    SizeType Size() const noexcept { return _usedSize; }

    // Modifiers
    void Reserve(SizeType count) {
        _allocate(count);
    }

    void SetData(const Span<TArrayType>& data) {
        if (data.IsEmpty()) {
            return;
        }

        if (_maxSize < data.Size()) {
            if (_data != nullptr) {
                delete[] _data;
            }
            _data = new TArrayType[data.Size()];
            _maxSize = data.Size();
            _usedSize = _maxSize;
        }

        for (unsigned int i{}; i < _maxSize; ++i) {
            _data[i] = data[i];
        }
    }

    void Add(const TArrayType& element) {
        if (_maxSize == 0) {
            _allocate(5);
        }

        if (_usedSize == _maxSize) {
            _allocate(_maxSize);
        }

        _data[_usedSize] = element;
        ++_usedSize;
    }

private:
    void _allocate(SizeType count) { 
        const SizeType dataSize = _maxSize + count;
        auto* data = new TArrayType[dataSize];
        if (_data != nullptr) {
            for (SizeType i = 0; i < _usedSize; ++i) {
                data[i] = _data[i];
            }
            delete[] _data;
        }
        _data = data;
        _maxSize = dataSize;
    }

    void _delete() {
        if (_data != nullptr) {
            delete[] _data;
            _data = nullptr;
        }
    }

    void _copy(const Array& other) {
        _data = new TArrayType[other._maxSize];
        for (SizeType i = 0; i < other._usedSize; ++i) {
            _data[i] = other[i];
        }
        _maxSize = other._maxSize;
        _usedSize = other._usedSize;
    }

    TArrayType* _data{};
    SizeType _maxSize{};
    SizeType _usedSize{};
};
} // namespace GraphicLib
