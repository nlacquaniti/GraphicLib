#pragma once

#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexBufferImpl : public VertexBuffer {
public:
    VertexBufferImpl();

private:
    unsigned int _getID() const override;
    void _bind() const override;
    void _unbind() const override;
    void _setData(const float* const vertexDataArray, unsigned int vertexDataArrayCount) const override;
    unsigned int _id{};
};
} // namespace OpenGLImpl
} // namespace GraphicLib
