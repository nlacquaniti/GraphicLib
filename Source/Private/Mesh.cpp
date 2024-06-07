#include "GraphicLib/Mesh.h"
#include "GraphicLib/VertexBuffer.h"
#include "InternalLogger.h"

namespace GraphicLib {
void Mesh::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already Initialised");
        return;
    }
    _vertexArray.Initialise();
    _id.IsInitialised = true;
}

void Mesh::Set(VertexBufferData&& vertexBufferData) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    _vertexArray.Set(std::move(vertexBufferData));
}

void Mesh::Draw(const Shader& shader) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    shader.Bind();
    for (size_t i{}; i < _textures.size(); ++i) {
        Texture& texture = _textures[i];
        _textures[i].SetTextureSlot(static_cast<unsigned int>(i));
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

const VertexArray& Mesh::GetVertexArray() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _vertexArray;
}

const std::vector<Texture>& Mesh::GetTextures() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _textures;
}
} // namespace GraphicLib
