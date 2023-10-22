#pragma once

#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexBufferImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const Span<float>& data, const Span<int>& attributes);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
