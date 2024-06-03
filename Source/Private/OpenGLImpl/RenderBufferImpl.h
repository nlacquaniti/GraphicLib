#pragma once

#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib::OpenGLImpl {
class RenderBufferImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned id, const RenderBufferData& data) const;
    void Delete(unsigned int& id) const;
};
} // namespace GraphicLib::OpenGLImpl
