#pragma once

#include <GraphicLib/FrameBuffer.h>

struct GLFWwindow;

template<typename TCallbackType>
struct WindowCallbackHandler {
    void Set(TCallbackType callback, void* userData) {
        Callback = callback;
        UserData = userData;
    }
    TCallbackType Callback{};
    void* UserData{};
};

class WindowImpl final {
public:
    static bool Create(int width, int height, const char* title);
    static void Render();
    static void Shutdown();
    static void GetSize(int& width, int& height);
    static GLFWwindow* GetWindowPtr();
    static const GraphicLib::FrameBuffer& GetFrameBuffer();

    static WindowCallbackHandler<void (*)(const char*, void*)> OnDebugLog;
    static WindowCallbackHandler<void (*)(void*)> OnRenderDraw;
    static WindowCallbackHandler<void (*)(void*)> OnRenderDrawDebug;
    static WindowCallbackHandler<void (*)(void*)> OnWindowClosed;
    static WindowCallbackHandler<void (*)(int, int, void*)> OnMouseInput;

private:
    static void _clear();
    static void _onWindowClosed(GLFWwindow* window);
    static void _onKeyPressed(GLFWwindow* window, int key, int, int action, int);
    static void _onMouseButtonCallback(GLFWwindow* window, int button, int action, int);
    static void _onSetWindowSize(GLFWwindow* window, int width, int height);
    static void _invokeLogCallback(const char* message);
    static void _setFrameBufferConfiguration();
    static GLFWwindow* _window;
    static GraphicLib::FrameBuffer _windowFrameBuffer;
};
