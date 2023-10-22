#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Shader final {
public:
    bool Load(const char* vertexShared, const char* fragmentShader);
    void Bind();
    void Unbind();
    void SetUniformValue(const char* name, bool value) const;
    void SetUniformValue(const char* name, int value) const;
    void SetUniformValue(const char* name, float value) const;
private:
    unsigned int _id{};
};
} // namespace GraphicLib
