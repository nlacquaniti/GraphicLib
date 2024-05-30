#pragma once

#include "GraphicLib/DLL_API.h"
#include <memory>
#include <string>
#include <vector>

namespace GraphicLib {
enum class ETextureType : unsigned char {
    NONE,
    TEXTURE_2D,
    CUBE_MAP,
};

enum class ETextureParamName : unsigned char {
    NONE,
    MIN_FILTER,
    MAG_FILTER,
    WRAP_S,
    WRAP_T,
};

enum class ETextureParamValue : unsigned char {
    NONE,
    FILTER_NEAREST,
    FILTER_LIEAR,
    WRAP_CLAMP_TO_EDGE,
    WRAP_CLAMP_TO_BORDER,
    WRAP_MIRRORED_REPEAT,
    WRAP_REPEAT,
    WRAP_MIRROR_CLAMP_TO_EDGE,
};

enum class ETextureChannel : unsigned char {
    NONE,
    GRAY,
    GRAY_ALPHA,
    RGB,
    RGBA,
    STENCIL,
    DEPTH,
    DEPTH_STENCIL,
};

enum class ETextureFormat : unsigned char {
    NONE,
    RGBA,
    RGB,
    RGBA8,
    RGBA16F,
    RGBA32F,
    SRGB8,
    SRGB8_ALPHA8,
    DEPTH,
    DEPTH16,
    DEPTH24,
    DEPTH32,
    DEPTH32F,
    STENCIL,
    STENCIL8,
    DEPTH24_STENCIL8,
    DEPTH32F_STENCIL8,
};

enum class ETextureDataType : unsigned char {
    NONE,
    UNSIGNED_BYTE,
    FLOAT,
    HALF_FLOAT,
    UNSIGNED_SHORT,
    INT,
    UNSIGNED_INT,
    UNSIGNED_INT_24_8,
};

struct TextureParam {
    ETextureParamName Name{};
    ETextureParamValue Value{};
};

struct SetTextureParams {
    std::string Name;
    int Width{};
    int Height{};
    ETextureChannel Channel{};
    ETextureFormat Format{};
    ETextureDataType DataType{};
};

struct TextureData {
    std::string FilePath;
    std::string Name;
    std::vector<TextureParam> Parameters;
    int Width{};
    int Height{};
    ETextureType Type{};
    ETextureChannel Channel{};
    ETextureFormat Format{};
    ETextureDataType DataType{};
};

class DLL_API Texture {
public:
    Texture() noexcept;
    Texture(Texture&&) = delete;
    Texture& operator=(Texture&&) = delete;
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    ~Texture() noexcept;
    void Bind() const;
    void Unbind() const;
    void ActivateUnit(unsigned int slot) const;
    void Set(ETextureType type, std::string&& texturePath, std::vector<TextureParam>&& params);
    void Set(ETextureType type, const SetTextureParams& setParams, std::vector<TextureParam>&& params);
    void Delete();
    [[nodiscard]] const TextureData& GetData() const;
    [[nodiscard]] unsigned int GetID() const;

private:
    TextureData _data{};
    unsigned int _id{};
};
} // namespace GraphicLib
