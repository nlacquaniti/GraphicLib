#pragma once

#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib::OpenGLImpl {
class RenderBufferImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned id, const RenderBufferData& data);
    static void Delete(unsigned int& id);
};
} // namespace GraphicLib::OpenGLImpl
