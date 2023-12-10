#pragma once

namespace GraphicLib {
namespace OpenGLImpl {
class FrameBufferImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Delete(unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
