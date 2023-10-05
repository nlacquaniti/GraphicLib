#pragma once

#include "GraphicLib/IndexBuffer.h"

namespace GraphicLib {
namespace OpenGLImpl {
class IndexBufferOpsImpl final {
public:
    static void InitialiseIndexBufferData(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void SendBufferToGPU(unsigned int id, const StackArraySpan<IndexBufferDataElement>& data);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
