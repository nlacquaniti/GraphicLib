#pragma once

namespace GraphicLib::Internal {
struct ShaderParameter {
    const char* Content;
    unsigned int Type;
};

struct ShaderData {
    static constexpr size_t MAX_PARAMETERS_COUNT = 6;
    ShaderParameter Parameters[MAX_PARAMETERS_COUNT];
};

#ifndef MOCK_OPENGL_IMPL
bool InitialiseShader(unsigned int* id,
    const Internal::ShaderData& data,
    size_t parametersCount,
    void (*onCompilationFailed)(const char*));
void BindShader(unsigned int id);
void UnbindShader();
void SetUniformBoolValueShader(unsigned int id, const char* name, bool value);
void SetUniformIntValueShader(unsigned int id, const char* name, int value);
void SetUniformFloatValueShader(unsigned int id, const char* name, float value);
void SetUniformMat4ValueShader(unsigned int id, const char* name, const float* value);
void DeleteShader(unsigned int* id);
#else
inline bool InitialiseShader(unsigned int* id,
    const Internal::ShaderData& data,
    size_t parametersCount,
    void (*onCompilationFailed)(const char*)) {
    return true;
}
inline void BindShader(unsigned int id) {
}
inline void UnbindShader() {
}
inline void SetUniformBoolValueShader(unsigned int id, const char* name, bool value) {
}
inline void SetUniformIntValueShader(unsigned int id, const char* name, int value) {
}
inline void SetUniformFloatValueShader(unsigned int id, const char* name, float value) {
}
inline void SetUniformMat4ValueShader(
    unsigned int id, const char* name, const float* value) {
}
inline void DeleteShader(unsigned int* id) {
}
#endif
} // namespace GraphicLib::Internal
