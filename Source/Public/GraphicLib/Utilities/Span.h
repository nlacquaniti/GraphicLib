#pragma once

namespace GraphicLib {
template<typename TSpanType>
class Span {
public:
    using SizeType = unsigned long long;

    Span() noexcept = default;

    template<SizeType SIZE>
    Span(TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    template<SizeType SIZE>
    Span(const TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    Span(TSpanType* arr, SizeType size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(const TSpanType* arr, SizeType size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(const Span& other) noexcept = default;
    Span& operator=(const Span& other) noexcept = default;

    template<SizeType SIZE>
    void SetData(TSpanType (&arr)[SIZE]) noexcept {
        _data = arr;
        _size = SIZE;
    }

    template<SizeType SIZE>
    void SetData(const TSpanType (&arr)[SIZE]) noexcept {
        _data = arr;
        _size = SIZE;
    }

    void SetData(TSpanType* arr, SizeType size) noexcept {
        _data = arr;
        _size = size;
    }

    void SetData(const TSpanType* arr, SizeType size) noexcept {
        _data = arr;
        _size = size;
    }

    const TSpanType& operator[](SizeType idx) const { return _data[idx]; }
    const TSpanType& Front() const { return *_data; }
    const TSpanType& Back() const { return &_data[size - 1]; }
    const TSpanType* Data() const { return _data; }

    SizeType Size() const { return _size; }
    SizeType SizeBytes() const { return sizeof(TSpanType) * _size; }
    bool IsEmpty() const { return _size == 0; }

private:
    const TSpanType* _data{};
    SizeType _size{};
};
} // namespace GraphicLib
