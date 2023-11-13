#include "Window.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/WindowImpl.h"
#else
#error "No WindowImpl has been detected."
#endif


Window::~Window() {
    _clear();
}

bool Window::Create(const WindowSize& size, const char* title, void* userData) {
    static bool _createdCalled{};
    bool bSuccess{};
    if (!_createdCalled) {
        bSuccess = WindowImpl::Create(size.Width, size.Height, title, userData);
        _userData = userData;
        _createdCalled = true;
    }

    return bSuccess;
}

void Window::Render() {
    WindowImpl::Render();
}

void Window::Shutdown() {
    _clear();
}

void Window::SetOnCloseCallback(CloseWindowCallback closeWindowCallback) {
    WindowImpl::SetWindowClosedCallback(closeWindowCallback);
}

void Window::SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback) {
    WindowImpl::SetRenderCallback(renderWindowCallback);
}

void Window::SetLogCallback(LogCallback logCallback) {
    WindowImpl::SetLogCallback(logCallback);
}

WindowSize Window::GetSize() const {
    WindowSize size;
    WindowImpl::GetSize(size.Width, size.Height);
    return size;
}

void Window::_clear() {
    _userData = nullptr;
    WindowImpl::Shutdown();
}
