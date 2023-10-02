#pragma once

#include "GraphicLib/Utilities/StackArray.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexBufferOpsImpl {
public:
    static void InitialiseVertexBufferData(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void SetData(unsigned int id, const StackArraySpan<unsigned int>& attributes, const StackArraySpan<float>& data);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
