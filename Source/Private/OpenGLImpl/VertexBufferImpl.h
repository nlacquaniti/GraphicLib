#pragma once

#include <vector>

namespace GraphicLib::OpenGLImpl {
class VertexBufferImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned int id, const std::vector<float>& data, const std::vector<int>& attributes) const;
    void Delete(unsigned int& id) const;
};
} // namespace GraphicLib::OpenGLImpl
