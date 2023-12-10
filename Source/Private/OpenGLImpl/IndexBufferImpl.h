#pragma once

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
namespace OpenGLImpl {
class IndexBufferImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned int id, const Span<IndexBufferDataElement>& data) const;
    void Delete(unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
