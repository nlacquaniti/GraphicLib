#pragma once

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
namespace OpenGLImpl {
class IndexBufferImpl final {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const Span<IndexBufferDataElement>& data);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
