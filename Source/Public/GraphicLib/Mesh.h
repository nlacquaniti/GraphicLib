#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Shader.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include "GraphicLib/VertexArray.h"
#include "GraphicLib/VertexBuffer.h"

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
    void Set(VertexBufferData&& vertexBufferData);
    void Draw(const Shader& shader);
    [[nodiscard]] const VertexArray& GetVertexArray() const;
    VertexArray& GetVertexArray();
    [[nodiscard]] const std::vector<Texture>& GetTextures() const;
    std::vector<Texture>& GetTextures();

private:
    VertexArray _vertexArray;
    UniqueIdentifier _id;
    std::vector<Texture> _textures;
};
} // namespace GraphicLib
