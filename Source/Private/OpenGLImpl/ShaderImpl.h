#pragma once

#include "GraphicLib/Shader.h"

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImpl final {
public:
    static bool Load(unsigned int& id, const char* vertexShared, const char* fragmentShader);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void SetUniformBoolValue(unsigned int id, const char* name, bool value);
    static void SetUniformIntValue(unsigned int id, const char* name, int value);
    static void SetUniformFloatValue(unsigned int id, const char* name, float value);
    static void SetUniformMat4Value(unsigned int id, const char* name, const float* value);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
