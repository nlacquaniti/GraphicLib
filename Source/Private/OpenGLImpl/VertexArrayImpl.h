#pragma once

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayImpl final {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
