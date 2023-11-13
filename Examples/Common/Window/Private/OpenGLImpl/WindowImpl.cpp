#include "WindowImpl.h"

#include "glad.h"
#define GLFW_INCLUDE_NONE
#include "glfw.h"

void* WindowImpl::_userData{};
WindowImpl::OnWindowClosedCallback WindowImpl::_onWindowClosedCallback{};
WindowImpl::OnRenderCallback WindowImpl::_onRenderCallback{};
WindowImpl::OnWindowLogCallback WindowImpl::_onWindowLogCallback{};
GLFWwindow* WindowImpl::_window{};

bool WindowImpl::Create(int width, int height, const char* title, void* userData) {
    if (width < 1 || height < 1) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window with either width or height with 0 or less value");
        return false;
    }

    if (title == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window without a title");
        return false;
    }

    _userData = userData;

    if (!glfwInit()) {
        _clear();
        return false;
    }

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_window == nullptr) {
        _clear();
        return false;
    }

    glfwSetWindowCloseCallback(_window, _onWindowClosed);
    glfwSetKeyCallback(_window, _onKeyPressed);
    glfwSetWindowSizeCallback(_window, _onSetWindowSize);

    glfwMakeContextCurrent(_window);
    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glfwSwapInterval(1);

    return true;
}

void WindowImpl::Render() {
    if (_window == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Render: GLFWwindow is null");
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    if (_onRenderCallback != nullptr) {
        _onRenderCallback(_userData);
    }

    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void WindowImpl::Shutdown() {
    _clear();
}

void WindowImpl::SetRenderCallback(OnRenderCallback onRenderCallback) {
    _onRenderCallback = onRenderCallback;
}

void WindowImpl::SetWindowClosedCallback(OnWindowClosedCallback onWindowClosedCallback) {
    _onWindowClosedCallback = onWindowClosedCallback;
}

void WindowImpl::SetLogCallback(OnWindowLogCallback onWindowLogCallback) {
    _onWindowLogCallback = onWindowLogCallback;
}

void WindowImpl::GetSize(int& width, int& height) {
    glfwGetWindowSize(_window, &width, &height);
}

void WindowImpl::_clear() {
    if (_window != nullptr) {
        glfwDestroyWindow(_window);
        _window = nullptr;
        glfwTerminate();
    }

    _userData = nullptr;
    _onWindowClosedCallback = nullptr;
    _onRenderCallback = nullptr;
    _onWindowLogCallback = nullptr;
}

void WindowImpl::_onWindowClosed(GLFWwindow*) {
    if (_onWindowClosedCallback != nullptr) {
        _onWindowClosedCallback(_userData);
    }
}

void WindowImpl::_onKeyPressed(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        _onWindowClosed(window);
    }
}

void WindowImpl::_onSetWindowSize(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
    Render();
}

void WindowImpl::_invokeLogCallback(const char* message) {
    if (_onWindowLogCallback != nullptr) {
        _onWindowLogCallback(message);
    }
}
