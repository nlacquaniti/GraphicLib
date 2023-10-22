#pragma once

struct GLFWwindow;

namespace GraphicLib {
namespace OpenGLImpl {
class WindowImpl final {
public:
    using OnRenderCallback = void (*)(void*);
    using OnWindowClosedCallback = void(*)(void*);

    static bool Create(int width, int height, const char* title, void* userData);
    static void Render();
    static void Shutdown();
    static void SetRenderCallback(OnRenderCallback onRenderCallback);
    static void SetWindowClosedCallback(OnWindowClosedCallback onWindowClosedCallback);
    static void GetSize(int& width, int& height);

private:
    static void _clear();
    static void _onWindowClosed(GLFWwindow* window);
    static void _onKeyPressed(GLFWwindow* window, int key, int, int action, int);
    static void _onSetWindowSize(GLFWwindow* window, int width, int height);

    static void* _userData;
    static OnWindowClosedCallback _onWindowClosedCallback;
    static OnRenderCallback _onRenderCallback;
    static unsigned long long _glfwLogSystemId;
    static unsigned long long _openGLLogSystemId;
    static GLFWwindow* _window;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
