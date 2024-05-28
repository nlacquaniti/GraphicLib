#pragma once

#include <vector>

namespace GraphicLib::OpenGLImpl {
class IndexBufferImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const std::vector<int>& data);
    static void Delete(unsigned int& id);
};
} // namespace GraphicLib::OpenGLImpl
