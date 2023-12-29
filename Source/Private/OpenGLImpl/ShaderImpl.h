#pragma once

#include "GraphicLib/Shader.h"
#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    bool Set(unsigned int id, const Span<ShaderData>& shadersData) const;
    void SetUniformBoolValue(unsigned int id, const char* name, bool value) const;
    void SetUniformIntValue(unsigned int id, const char* name, int value) const;
    void SetUniformFloatValue(unsigned int id, const char* name, float value) const;
    void SetUniformMat4Value(unsigned int id, const char* name, const float* value) const;
    void Delete(unsigned int& id) const;
private:
    bool _createShader(const ShaderData& shaderData, unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
