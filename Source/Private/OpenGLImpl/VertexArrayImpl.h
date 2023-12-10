#pragma once

namespace GraphicLib {
namespace OpenGLImpl {
class VertexArrayImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void DrawTriangles(unsigned int id, int trianglesCount) const;
    void DrawVertices(unsigned int id, int verticesCount) const;
    void Delete(unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
