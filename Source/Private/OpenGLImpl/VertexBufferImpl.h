#pragma once

#include "GraphicLib/VertexBuffer.h"
#include <vector>

namespace GraphicLib::OpenGLImpl {
class VertexBufferImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const std::vector<float>& data, const std::vector<VertexAttribute>& attributes);
    static void Delete(unsigned int& id);
};
} // namespace GraphicLib::OpenGLImpl
