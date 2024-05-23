#pragma once

#include "DLL_API.h"
#include <string>
#include <vector>

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

struct ShaderData {
    std::string FilePath{};
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
    void Set(std::vector<ShaderData>&& data);
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
    void Delete();
    const std::vector<ShaderData>& GetData() const;
    unsigned int GetID() const;

private:
    std::vector<ShaderData> _data{};
    unsigned int _id{};
};
} // namespace GraphicLib
