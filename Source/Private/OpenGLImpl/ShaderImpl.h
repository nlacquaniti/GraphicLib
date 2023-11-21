#pragma once

#include "GraphicLib/Shader.h"

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImpl final {
public:
    bool Load(unsigned int& id, const char* vertexShared, const char* fragmentShader) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void SetUniformBoolValue(unsigned int id, const char* name, bool value) const;
    void SetUniformIntValue(unsigned int id, const char* name, int value) const;
    void SetUniformFloatValue(unsigned int id, const char* name, float value) const;
    void SetUniformMat4Value(unsigned int id, const char* name, const float* value) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
