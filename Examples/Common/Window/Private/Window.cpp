#include "Window/Window.h"

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
        bSuccess = WindowImpl::Create(size.Width, size.Height, title);
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

void Window::SetLogCallback(LogCallback logCallback) {
    WindowImpl::OnDebugLog.Set(logCallback, _userData);
}

void Window::SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback) {
    WindowImpl::OnRenderDraw.Set(renderWindowCallback, _userData);
}

void Window::SetOnRenderWindowDebugCallback(RenderWindowDebugCallback renderWindowDebugCallback) {
    WindowImpl::OnRenderDrawDebug.Set(renderWindowDebugCallback, _userData);
}

void Window::SetOnCloseCallback(CloseWindowCallback closeWindowCallback) {
    WindowImpl::OnWindowClosed.Set(closeWindowCallback, _userData);
}

void Window::SetMouseInputCallback(MouseInputCallback mouseInputCallback) {
    _mouseInputCallback = mouseInputCallback;
    WindowImpl::OnMouseInput.Set(_internalSetMouseInputCallback, this);
}

WindowSize Window::GetSize() const {
    WindowSize size;
    WindowImpl::GetSize(size.Width, size.Height);
    return size;
}

void* Window::GetWindowImplPtr() const {
    return WindowImpl::GetWindowPtr();
}

void* Window::GetUserData() const {
    return _userData;
}

void Window::_internalSetMouseInputCallback(int button, int action, void* userData) {
    const auto* window = static_cast<Window*>(userData);
    window->_mouseInputCallback(static_cast<EMouseButton>(button), static_cast<EInputAction>(action), window->GetUserData());
}

void Window::_clear() {
    _userData = nullptr;
    WindowImpl::Shutdown();
}
