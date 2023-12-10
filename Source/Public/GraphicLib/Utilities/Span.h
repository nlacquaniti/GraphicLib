#pragma once

namespace GraphicLib {
template<typename TSpanType>
class Span final {
public:
    Span() noexcept = default;

    template<unsigned long long SIZE>
    Span(TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    template<unsigned long long SIZE>
    Span(const TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    Span(TSpanType* arr, unsigned long long size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(const TSpanType* arr, unsigned long long size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(const Span& other) noexcept = default;
    Span& operator=(const Span& other) noexcept = default;

    template<unsigned long long SIZE>
    void SetData(TSpanType (&arr)[SIZE]) noexcept {
        _data = arr;
        _size = SIZE;
    }

    template<unsigned long long SIZE>
    void SetData(const TSpanType (&arr)[SIZE]) noexcept {
        _data = arr;
        _size = SIZE;
    }

    void SetData(TSpanType* arr, unsigned long long size) noexcept {
        _data = arr;
        _size = size;
    }

    void SetData(const TSpanType* arr, unsigned long long size) noexcept {
        _data = arr;
        _size = size;
    }

    const TSpanType& operator[](unsigned long long idx) const { return _data[idx]; }
    const TSpanType& Front() const { return *_data; }
    const TSpanType& Back() const { return &_data[size - 1]; }
    const TSpanType* Data() const { return _data; }

    unsigned long long Size() const { return _size; }
    unsigned long long SizeBytes() const { return sizeof(TSpanType) * _size; }
    bool IsEmpty() const { return _size == 0; }

private:
    const TSpanType* _data{};
    unsigned long long _size{};
};
} // namespace GraphicLib
