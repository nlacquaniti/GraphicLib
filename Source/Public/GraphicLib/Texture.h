#pragma once

#include "GraphicLib/DLL_API.h"
#include "Utilities/Array.h"
#include "Utilities/Span.h"

namespace GraphicLib {
enum class TextureType : unsigned char {
    NONE,
    TEXTURE_2D,
    CUBE_MAP,
};

enum class TextureParamName : unsigned char {
    NONE,
    MIN_FILTER,
    MAG_FILTER,
    WRAP_S,
    WRAP_T,
};

enum class TextureParamValue : unsigned char {
    NONE,
    FILTER_NEAREST,
    FILTER_LIEAR,
    WRAP_CLAMP_TO_EDGE,
    WRAP_CLAMP_TO_BORDER,
    WRAP_MIRRORED_REPEAT,
    WRAP_REPEAT,
    WRAP_MIRROR_CLAMP_TO_EDGE,
};

enum class TextureChannel : unsigned char {
    NONE,
    GRAY,
    GRAY_ALPHA,
    RGB,
    RGBA,
};

struct TextureParam {
    TextureParamName Name{};
    TextureParamValue Value{};
};

struct TextureData {
    TextureType Type{};
    TextureChannel Channel{};
    int Width{};
    int Height{};
    Array<char> FilePath{};
    Array<TextureParam> Parameters{};
    Span<unsigned char> PixelData{};
};

class DLL_API Texture final {
public:
    Texture() = default;
    Texture(const Texture& other) = default;
    Texture& operator=(const Texture& other) = default;
    ~Texture();
    void Initialise();
    void Bind();
    void Unbind();
    void Draw(unsigned char slot);
    void Set(const char* filePath, TextureType type, const Span<TextureParam>& params);
    const TextureData& GetData() const;
    unsigned int GetID() const;

private:
    TextureData _data{};
    unsigned char* _pixelData{};
    unsigned int _id;
};
} // namespace GraphicLib
