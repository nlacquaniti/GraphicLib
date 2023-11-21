#pragma once

struct GLFWwindow;

class WindowImpl final {
public:
    using OnRenderCallback = void (*)(void*);
    using OnRenderDebugCallback = void(*)(void*);
    using OnWindowClosedCallback = void(*)(void*);
    using OnWindowLogCallback = void(*)(const char*);

    static bool Create(int width, int height, const char* title, void* userData);
    static void Render();
    static void Shutdown();
    static void SetRenderCallback(OnRenderCallback onRenderCallback);
    static void SetRenderDebugCallback(OnRenderDebugCallback onRenderDebugCallback);
    static void SetWindowClosedCallback(OnWindowClosedCallback onWindowClosedCallback);
    static void SetLogCallback(OnWindowLogCallback onWindowLogCallback);
    static void GetSize(int& width, int& height);
    static GLFWwindow* GetWindowPtr();

private:
    static void _clear();
    static void _onWindowClosed(GLFWwindow* window);
    static void _onKeyPressed(GLFWwindow* window, int key, int, int action, int);
    static void _onSetWindowSize(GLFWwindow* window, int width, int height);
    static void _invokeLogCallback(const char* message);

    static void* _userData;
    static OnWindowClosedCallback _onWindowClosedCallback;
    static OnRenderCallback _onRenderCallback;
    static OnRenderDebugCallback _onRenderDebugCallback;
    static OnWindowLogCallback _onWindowLogCallback;
    static GLFWwindow* _window;
};
