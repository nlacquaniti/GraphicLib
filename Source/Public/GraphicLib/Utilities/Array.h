#pragma once

#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
template<typename TArrayType>
class Array final {
public:
    // Member Functions
    explicit Array() noexcept = default;
    Array(const Array& other) = default;
    Array& operator=(const Array& other) = default;
    ~Array() {
        delete[] _data;
        _data = nullptr;
    }

    // Element Access
    TArrayType& operator[](unsigned long long pos) { return _data[pos]; }
    const TArrayType& operator[](unsigned long long pos) const { return _data[pos]; }

    TArrayType& Front() { return *_data; }
    const TArrayType& Front() const { return *_data; }

    TArrayType& Back() { return *_data[_size == 0 ? 0 : _size - 1]; }
    const TArrayType& Back() const { return *_data[_size == 0 ? 0 : _size - 1]; }

    TArrayType* Data() noexcept { return _data; }
    const TArrayType* Data() const noexcept { return _data; }

    // Capacity
    bool IsEmpty() const noexcept { return _size == 0; }
    unsigned long long Size() const noexcept { return _size; }

    // Modifiers
    void SetData(const Span<TArrayType>& data) {
        if (data.IsEmpty()) {
            return;
        }

        if (_size < data.Size()) {
            if (_data != nullptr) {
                delete[] _data;
            }
            _data = new TArrayType[data.Size()];
            _size = data.Size();
        }

        for (unsigned int i{}; i < _size; ++i) {
            _data[i] = data[i];
        }
    }

private:
    TArrayType* _data{};
    unsigned long long _size{};
};
} // namespace GraphicLib
