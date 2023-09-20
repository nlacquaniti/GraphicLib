#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API VertexBuffer {
public:
    static VertexBuffer* Create();
    virtual ~VertexBuffer() = default;
    VertexBuffer(const VertexBuffer& other) = delete;
    VertexBuffer& operator=(const VertexBuffer& other) = delete;
    unsigned int GetID() const;
    void Bind() const;
    void Unbind() const;
    void SetData(const float* const vertexDataArray, unsigned int vertexDataArrayCount) const;

protected:
    VertexBuffer() = default;
    
private:
    virtual unsigned int _getID() const = 0;
    virtual void _bind() const = 0;
    virtual void _unbind() const = 0;
    virtual void _setData(const float* const vertexDataArray, unsigned int vertexDataArrayCount) const = 0;
};
} // namespace GraphicLib
