#pragma once

#include "DLL_API.h"
#include "GraphicLib/Shader.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/VertexArray.h"

namespace GraphicLib {
class DLL_API Mesh {
public:
    Mesh() noexcept = default;
    Mesh(Mesh&& other) = delete;
    Mesh& operator=(Mesh&& other) = delete;
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
    ~Mesh() noexcept = default;
    void Draw(const Shader& shader);
    [[nodiscard]] const VertexArray& GetVertexArray() const;
    VertexArray& GetVertexArray();
    [[nodiscard]] const std::vector<Texture>& GetTextures() const;
    std::vector<Texture>& GetTextures();

private:
    VertexArray _vertexArray;
    std::vector<Texture> _textures;
};
} // namespace GraphicLib
