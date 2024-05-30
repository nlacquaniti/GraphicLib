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
    std::string FilePath;
    EShaderType Type{};
};

class DLL_API Shader {
public:
    Shader() noexcept;
    Shader(Shader&&) = delete;
    Shader& operator=(Shader&&) = delete;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader() noexcept;
    void Bind() const;
    void Unbind() const;
    void Set(std::vector<ShaderData>&& data);
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
    void Delete();
    [[nodiscard]] const std::vector<ShaderData>& GetData() const;
    [[nodiscard]] unsigned int GetID() const;

private:
    std::vector<ShaderData> _data;
    unsigned int _id{};
};
} // namespace GraphicLib
