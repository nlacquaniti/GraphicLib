#pragma once

#include "GraphicLib/IndexBuffer.h"

namespace GraphicLib {
namespace OpenGLImpl {
class IndexBufferImpl final : public IndexBuffer {
public:
    IndexBufferImpl();

private:
    unsigned int _getID() const override;
    void _bind() const override;
    void _unbind() const override;
    void _setData(const unsigned int* const dataArray, unsigned int dataArrayCount) const override;
    unsigned int _id{};
};
} // namespace OpenGLImpl
} // namespace GraphicLib
