#pragma once

namespace GraphicLib::OpenGLImpl {
class VertexArrayImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void DrawTriangles(unsigned int id, int trianglesCount) const;
    void DrawVertices(unsigned int id, int verticesCount) const;
    void Delete(unsigned int& id) const;
};
} // namespace GraphicLib::OpenGLImpl
