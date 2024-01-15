#pragma once

#include "Utils/CallbackHandler.h"
#include <GraphicLib/FrameBuffer.h>

struct GLFWwindow;

class WindowImpl {
public:
    static bool Create(const char* title);
    static void Update();
    static void Shutdown();
    static void GetSize(int& width, int& height);
    static GLFWwindow* GetWindowPtr();
    static const GraphicLib::FrameBuffer& GetFrameBuffer();

    static CallbackHandler<void (*)(const char*, void*)> OnDebugLog;
    static CallbackHandler<void (*)(float, void*)> OnUpdate;
    static CallbackHandler<void (*)(void*)> OnRenderDraw;
    static CallbackHandler<void (*)(void*)> OnRenderDrawDebug;
    static CallbackHandler<void (*)(void*)> OnWindowClosed;

private:
    static void _clear();
    static void _onWindowClosed(GLFWwindow* window);
    static void _onSetWindowSize(GLFWwindow* window, int width, int height);
    static void _invokeLogCallback(const char* message);
    static void _setFrameBufferConfiguration();
    static GLFWwindow* _window;
    static GraphicLib::FrameBuffer _windowFrameBuffer;
};
