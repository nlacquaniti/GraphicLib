#pragma once

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Draw(unsigned int id, int trianglesCount) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
