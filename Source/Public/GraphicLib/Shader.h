#pragma once

#include "DLL_API.h"
#include "Utilities/Array.h"
#include "Utilities/Span.h"

namespace GraphicLib {
enum class EShaderType : unsigned char {
    NONE,
    VERTEX,
    FRAGMENT,
    COMPUTE,
    GEOMETRY,
    TESS_CONTROL,
    TESS_EVALUATION,
};

struct ShaderParam {
    Span<char> FilePath{};
    EShaderType Type{};
};

struct ShaderData {
    Array<char> FilePath{};
    EShaderType Type{};
};

class DLL_API Shader {
public:
    Shader() = default;
    Shader(const Shader& other) = default;
    Shader& operator=(const Shader& other) = default;
    ~Shader();
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(const Span<ShaderParam>& params);
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
    void Delete();
    Span<ShaderData> GetData() const;
    unsigned int GetID() const;

private:
    unsigned int _id{};
    Array<ShaderData> _data{};
};
} // namespace GraphicLib
