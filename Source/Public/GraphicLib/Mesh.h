#pragma once

#include "DLL_API.h"
#include "GraphicLib/Shader.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/VertexArray.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
class DLL_API Mesh {
public:
    Mesh() = default;
    Mesh(Mesh&& other) = default;
    Mesh& operator=(Mesh&& other) = default;
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
    ~Mesh() = default;
    void Initialise();
    void Set(std::vector<float>&& vertexData, std::vector<VertexAttribute>&& vertexAttributes, std::vector<int>&& indices, std::vector<Texture>&& textures);
    void Draw(const Shader& shader);
    VertexArray& GetVertexArray();
    [[nodiscard]] const VertexArray& GetVertexArray() const;
    [[nodiscard]] const std::vector<Texture>& GetTextures() const;

private:
    VertexArray _vertexArray;
    std::vector<Texture> _textures;
};
} // namespace GraphicLib
