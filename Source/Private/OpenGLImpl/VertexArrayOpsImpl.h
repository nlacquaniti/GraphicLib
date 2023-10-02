#pragma once

#include "GraphicLib/VertexArray.h"

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayOpsImpl final {
public:
    static void InitialiseVertexArrayData(unsigned int& id);
    static void Bind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId);
    static void Unbind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
