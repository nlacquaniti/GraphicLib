#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Shader {
public:
    static Shader* Create();
    virtual ~Shader() = default;
    Shader(const Shader& other) = delete;
    Shader& operator=(const Shader& other) = delete;
    bool Load(const char* vertexShared, const char* fragmentShader);
    void Bind();
    void Unbind();
    unsigned int GetID() const;
    void SetUniformValue(const char* name, int value) const;

protected:
    Shader() = default;

private:
    virtual bool _load(const char* vertexShared, const char* fragmentShader) = 0;
    virtual void _bind() = 0;
    virtual void _unbind() = 0;
    virtual unsigned int _getID() const = 0;
    virtual void _setUniformValue(const char* name, int value) const = 0;
};
} // namespace GraphicLib
