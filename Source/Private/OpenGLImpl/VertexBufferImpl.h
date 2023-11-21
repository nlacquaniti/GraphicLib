#pragma once

#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexBufferImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned int id, const Span<float>& data, const Span<int>& attributes) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
