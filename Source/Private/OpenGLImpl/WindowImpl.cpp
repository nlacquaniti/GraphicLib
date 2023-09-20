#include "OpenGLImpl/WindowImpl.h"

#include "OpenGLImpl/glad.h"
#define GLFW_INCLUDE_NONE
#include "OpenGLImpl/glfw.h"

#include "InternalLogger.h"
#include "OpenGLImpl/GLFWLogSystem.h"
#include "OpenGLImpl/OpenGLLogSystem.h"
#include <cassert>
#include <limits>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
void WindowCloseCallback(GLFWwindow* window) {
    auto* windowImpl = static_cast<WindowImpl*>(glfwGetWindowUserPointer(window));
    assert(windowImpl != nullptr);
    windowImpl->CallOnCloseWindowCallback();
}
void WindowOnKeyPressedCallback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        WindowCloseCallback(window);
    }
}
} // namespace

WindowImpl::WindowImpl(unsigned int width, unsigned int height, const char* title)
    : _name(title)
    , _width(width)
    , _height(height) {
    assert(_width != 0 && _height != 0 && title != nullptr);
}

WindowImpl::~WindowImpl() {
    _clear();
}

void WindowImpl::CallOnCloseWindowCallback() {
    _closeWindowCallback(_closeWindowUserData);
}

void WindowImpl::_initialise() {
    _glfwLogSystemId = InternalLogger::Get().AttachExternalLogSystem(std::make_unique<GLFWLogSystem>());
    _openGLLogSystemId = InternalLogger::Get().AttachExternalLogSystem(std::make_unique<OpenGLLogSystem>());

    assert(glfwInit());
    assert(_width <= std::numeric_limits<int>::max());
    assert(_height <= std::numeric_limits<int>::max());
    _window = glfwCreateWindow(static_cast<int>(_width), static_cast<int>(_height), _name.c_str(), nullptr, nullptr);
    assert(_window != nullptr);

    glfwSetWindowUserPointer(_window, static_cast<void*>(this));
    glfwSetWindowCloseCallback(_window, WindowCloseCallback);
    glfwSetKeyCallback(_window, WindowOnKeyPressedCallback);

    glfwMakeContextCurrent(_window);

    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    _initialised = true;
    glfwSwapInterval(1);
}

void WindowImpl::_render() {
    assert(_initialised);

    if (glfwWindowShouldClose(_window)) {
        return;
    }

    int width{};
    int height{};
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    _renderWindowCallback(_renderWindowUserData);
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void WindowImpl::_shutdown() {
    _clear();
}

void WindowImpl::_setOnCloseCallback(CloseWindowCallback closeWindowCallback, void* userData) {
    _closeWindowCallback = closeWindowCallback;
    _closeWindowUserData = userData;
}

void WindowImpl::_setOnRenderWindowCallback(RenderWindowCallback renderWindowCallback, void* userData) {
    _renderWindowCallback = renderWindowCallback;
    _renderWindowUserData = userData;
}

unsigned int WindowImpl::_getWidth() const {
    return _width;
}

unsigned int WindowImpl::_getHeight() const {
    return _height;
}

void WindowImpl::_clear() {
    assert(_initialised);
    glfwDestroyWindow(_window);
    _window = nullptr;
    glfwTerminate();
    InternalLogger::Get().DetachExternalLogSystem(_glfwLogSystemId);
    InternalLogger::Get().DetachExternalLogSystem(_openGLLogSystemId);
    _initialised = false;
}
} // namespace OpenGLImpl
} // namespace GraphicLib
