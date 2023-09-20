#pragma once

#include "GraphicLib/Shader.h"

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImpl final : public Shader {
private:
    bool _load(const char* vertexShared, const char* fragmentShader) override;
    void _bind() override;
    void _unbind() override;
    unsigned int _getID() const override;
    void _setUniformValue(const char* name, int value) const override;
    unsigned int _id{};
};
} // namespace OpenGLImpl
} // namespace GraphicLib
