#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Shader.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include "GraphicLib/VertexArray.h"
#include "GraphicLib/VertexBuffer.h"
#include <vector>

namespace GraphicLib {
class DLL_API Mesh {
public:
    Mesh() noexcept = default;
    Mesh(Mesh&& other) noexcept = default;
    Mesh& operator=(Mesh&& other) noexcept = default;
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
    ~Mesh() noexcept = default;
    void Initialise();
    void SetVertexBuffer(std::vector<float>&& vertexData, const std::span<const VertexAttribute>& vertexAttributes);
    void SetIndexBuffer(std::vector<unsigned int>&& indices);
    void SetTextures(std::vector<TextureData>&& texturesData);
    void Draw(const Shader& shader);
    [[nodiscard]] const VertexArray& GetVertexArray() const;
    [[nodiscard]] const std::vector<Texture>& GetTextures() const;

private:
    VertexArray _vertexArray;
    std::vector<Texture> _textures;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
