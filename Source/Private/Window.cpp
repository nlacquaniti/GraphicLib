#include "GraphicLib/Window.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/WindowImpl.h"
using WindowImpl = GraphicLib::OpenGLImpl::WindowImpl;
#else
#error "No WindowImpl has been detected."
#endif

namespace GraphicLib {
void Window::Initialise() {
    _initialise();
}

void Window::Render() {
    _render();
}

void Window::Shutdown() {
    _shutdown();
}

unsigned int Window::GetWidth() const {
    return _getWidth();
}

unsigned int Window::GetHeight() const {
    return _getHeight();
}

void Window::SetOnCloseCallback(CloseWindowCallback closeWindowCallback, void* userData) {
    _setOnCloseCallback(closeWindowCallback, userData);
}

void Window::SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback, void* userData) {
    _setOnRenderWindowCallback(renderWindowCallback, userData);
}

Window* CreateWindow(unsigned int width, unsigned int height, const char* title) {
    return new WindowImpl(width, height, title);
}

} // namespace GraphicLib
