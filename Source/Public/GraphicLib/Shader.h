#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
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
    Shader() noexcept = default;
    Shader(Shader&&) noexcept = default;
    Shader& operator=(Shader&&) noexcept = default;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader() noexcept;
    void Initialise(std::vector<ShaderData>&& data);
    void Bind() const;
    void Unbind() const;
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
    [[nodiscard]] const std::vector<ShaderData>& GetData() const;
    [[nodiscard]] unsigned int GetID() const;

private:
    std::vector<ShaderData> _data;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
