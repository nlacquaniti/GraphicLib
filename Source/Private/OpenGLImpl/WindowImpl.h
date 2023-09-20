#pragma once

#include "GraphicLib/Window.h"

#include <string>

struct GLFWwindow;
namespace GraphicLib {
namespace OpenGLImpl {
class WindowImpl : public Window {
public:
    WindowImpl(unsigned int width, unsigned int height, const char* title);
    ~WindowImpl() override;
    void CallOnCloseWindowCallback();

private:
    void _initialise() override;
    void _render() override;
    void _shutdown() override;
    void _setOnCloseCallback(CloseWindowCallback closeWindowCallback, void* userData) override;
    void _setOnRenderWindowCallback(RenderWindowCallback renderWindowCallback, void* userData) override;
    unsigned int _getWidth() const override;
    unsigned int _getHeight() const override;
    void _clear();
    const std::string _name;
    std::size_t _glfwLogSystemId{};
    std::size_t _openGLLogSystemId{};
    GLFWwindow* _window{};
    CloseWindowCallback _closeWindowCallback{};
    RenderWindowCallback _renderWindowCallback{};
    void* _closeWindowUserData{};
    void* _renderWindowUserData{};
    unsigned int _width{};
    unsigned int _height{};
    bool _initialised{};
};
} // namespace OpenGLImpl
} // namespace GraphicLib
