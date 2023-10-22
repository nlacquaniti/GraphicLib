#pragma once

#include "GraphicLib/Shader.h"

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImpl final {
public:
    static bool Load(unsigned int& id, const char* vertexShared, const char* fragmentShader);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void SetUniformValue(unsigned int id, const char* name, bool value);
    static void SetUniformValue(unsigned int id, const char* name, int value);
    static void SetUniformValue(unsigned int id, const char* name, float value);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
