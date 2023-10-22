#pragma once

namespace GraphicLib {
template<typename TSpanType>
class Span final {
public:
    template<unsigned int SIZE>
    Span(TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    template<unsigned int SIZE>
    Span(const TSpanType (&arr)[SIZE]) noexcept
        : _data(arr)
        , _size(SIZE) {}

    Span(const TSpanType* arr, unsigned int size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(TSpanType* arr, unsigned int size) noexcept
        : _data(arr)
        , _size(size) {}

    Span(const Span& other) noexcept = default;
    Span& operator=(const Span& other) noexcept = default;

    const TSpanType& operator[](unsigned int idx) const { return _data[idx]; }
    const TSpanType& Front() const { return *_data; }
    const TSpanType& Back() const { return &_data[size - 1]; }
    const TSpanType* Data() const { return _data; }

    unsigned int Size() const { return _size; }
    unsigned int SizeBytes() const { return sizeof(TSpanType) * _size; }
    bool IsEmpty() const { return _size == 0; }

private:
    const TSpanType* _data{};
    unsigned int _size{};
};
} // namespace GraphicLib
