#include "GraphicLib/Mesh.h"

namespace GraphicLib {
void Mesh::Draw(const Shader& shader) {
    shader.Bind();
    for (size_t i{}; i < _textures.size(); ++i) {
        Texture& texture = _textures[i];
        _textures[i].ActivateUnit(static_cast<unsigned int>(i));
        shader.SetUniformIntValue(texture.GetData().Name.c_str(), static_cast<int>(i));
        texture.Bind();
    }

    _vertexArray.Bind();
    _vertexArray.Draw();

    for (size_t i{}; i < _textures.size(); ++i) {
        _textures[i].Unbind();
    }
    _vertexArray.Unbind();
}

VertexArray& Mesh::GetVertexArray() {
    return _vertexArray;
}

const VertexArray& Mesh::GetVertexArray() const {
    return _vertexArray;
}

const std::vector<Texture>& Mesh::GetTextures() const {
    return _textures;
}
} // namespace GraphicLib
