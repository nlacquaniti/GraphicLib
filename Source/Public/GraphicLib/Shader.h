#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <array>
#include <span>

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
    static constexpr std::size_t MAX_FILE_PATH_SIZE = 256;
    std::array<char, MAX_FILE_PATH_SIZE> FilePath{};
    EShaderType Type{};
};

class DLL_API Shader {
public:
    static constexpr std::size_t MAX_DATA_COUNT = static_cast<size_t>(EShaderType::TESS_EVALUATION);
    Shader() noexcept = default;
    Shader(Shader&&) noexcept = default;
    Shader& operator=(Shader&&) noexcept = default;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader() noexcept;
    void Initialise(const std::span<const ShaderData>& data);
    void Bind() const;
    void Unbind() const;
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
    [[nodiscard]] std::span<const ShaderData> GetData() const;
    [[nodiscard]] unsigned int GetID() const;

private:
    std::array<ShaderData, MAX_DATA_COUNT> _data;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
