#pragma once

#include "GraphicLib/Shader.h"
#include <vector>

namespace GraphicLib::OpenGLImpl {
class ShaderImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const std::vector<ShaderData>& shadersData);
    static void SetUniformBoolValue(unsigned int id, const char* name, bool value);
    static void SetUniformIntValue(unsigned int id, const char* name, int value);
    static void SetUniformFloatValue(unsigned int id, const char* name, float value);
    static void SetUniformMat4Value(unsigned int id, const char* name, const float* value);
    static void Delete(unsigned int& id);
};
} // namespace GraphicLib::OpenGLImpl
