#pragma once

#include "GraphicLib/VertexArray.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayImpl : public VertexArray {
public:
    VertexArrayImpl();

private:
    unsigned int _getID() const override;
    void _bind() const override;
    void _unbind() const override;
    unsigned int _id = 0;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
