#pragma once

namespace GraphicLib::OpenGLImpl {
class VertexArrayImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void DrawTriangles(unsigned int id, int trianglesCount);
    static void DrawVertices(unsigned int id, int verticesCount);
    static void Delete(unsigned int& id);
};
} // namespace GraphicLib::OpenGLImpl
