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

void Mesh::SetVertexBuffer(std::vector<float>&& vertexData, const std::span<const VertexAttribute>& vertexAttributes) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    _vertexArray.SetVertexBuffer(std::move(vertexData), vertexAttributes);
}

void Mesh::SetIndexBuffer(std::vector<IndexBufferDataElement>&& indices) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    _vertexArray.SetIndexBuffer(std::move(indices));
}

void Mesh::SetTextures(std::vector<TextureData>&& texturesData) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    _textures.reserve(texturesData.size());
    for (auto& textureData : texturesData) {
        Texture& texture = _textures.emplace_back();
        texture.Initialise();
        texture.Set(std::move(textureData));
    }
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

    _vertexArray.Draw();

    _vertexArray.Unbind();
    for (size_t i{}; i < _textures.size(); ++i) {
        _textures[i].Unbind();
    }
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
