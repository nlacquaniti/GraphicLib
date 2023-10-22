#pragma once

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayImpl final {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Draw(unsigned int id, unsigned int trianglesCount);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
