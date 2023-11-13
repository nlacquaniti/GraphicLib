#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Shader final {
public:
    bool Load(const char* vertexShared, const char* fragmentShader);
    void Bind();
    void Unbind();
    void SetUniformBoolValue(const char* name, bool value) const;
    void SetUniformIntValue(const char* name, int value) const;
    void SetUniformFloatValue(const char* name, float value) const;
    void SetUniformMat4Value(const char* name, float* value) const;
private:
    unsigned int _id{};
};
} // namespace GraphicLib
