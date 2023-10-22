#include "OpenGLImpl/WindowImpl.h"

#include "OpenGLImpl/glad.h"
#define GLFW_INCLUDE_NONE
#include "OpenGLImpl/glfw.h"

#include "InternalLogger.h"
#include "OpenGLImpl/GLFWLogSystem.h"
#include "OpenGLImpl/OpenGLLogSystem.h"
#include <limits>

namespace GraphicLib {
namespace OpenGLImpl {
void* WindowImpl::_userData{};
WindowImpl::OnWindowClosedCallback WindowImpl::_onWindowClosedCallback{};
WindowImpl::OnRenderCallback WindowImpl::_onRenderCallback{};
unsigned long long WindowImpl::_glfwLogSystemId{};
unsigned long long WindowImpl::_openGLLogSystemId{};
GLFWwindow* WindowImpl::_window{};

bool WindowImpl::Create(int width, int height, const char* title, void* userData) {
    if (width < 1 || height < 1) {
        InternalLogger::Get().LogInternalError("OpenGLImpl::WindowImpl::Create", "Cannot create a window with either width or height with 0 or less value");
        return false;
    }

    if (title == nullptr) {
        InternalLogger::Get().LogInternalError("OpenGLImpl::WindowImpl::Create", "Cannot create a window without a title");
        return false;
    }

    _userData = userData;
    _glfwLogSystemId = InternalLogger::Get().AttachExternalLogSystem(std::make_unique<GLFWLogSystem>());

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
    _openGLLogSystemId = InternalLogger::Get().AttachExternalLogSystem(std::make_unique<OpenGLLogSystem>());
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glfwSwapInterval(1);

    return true;
}

void WindowImpl::Render() {
    if (_window == nullptr) {
        InternalLogger::Get().LogInternalError("OpenGLImpl::WindowImpl::Render", "GLFWwindow is null");
        return;
    }

    int width{};
    int height{};

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
    InternalLogger::Get().DetachExternalLogSystem(_glfwLogSystemId);
    _glfwLogSystemId = {};
    InternalLogger::Get().DetachExternalLogSystem(_openGLLogSystemId);
    _openGLLogSystemId = {};
    _onWindowClosedCallback = nullptr;
    _onRenderCallback = nullptr;
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
} // namespace OpenGLImpl
} // namespace GraphicLib
