#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API IndexBuffer {
public:
    static IndexBuffer* Create();
    virtual ~IndexBuffer() = default;
    IndexBuffer(const IndexBuffer& other) = delete;
    IndexBuffer& operator=(const IndexBuffer& other) = delete;
    unsigned int GetID() const;
    void Bind() const;
    void Unbind() const;
    void SetData(const unsigned int* const dataArray, unsigned int dataArrayCount);

protected:
    IndexBuffer() = default;

private:
    virtual unsigned int _getID() const = 0;
    virtual void _bind() const = 0;
    virtual void _unbind() const = 0;
    virtual void _setData(const unsigned int* const dataArray, unsigned int dataArrayCount) const = 0;
};
} // namespace GraphicLib
