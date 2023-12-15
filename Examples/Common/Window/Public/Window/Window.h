#pragma once

#include "Window/Input.h"

namespace GraphicLib {
class FrameBuffer;
};

struct WindowSize {
    int Width{};
    int Height{};
};

class Window final {
public:
    using LogCallback = void (*)(const char*, void*);
    using RenderWindowCallback = void (*)(void*);
    using RenderWindowDebugCallback = void (*)(void*);
    using CloseWindowCallback = void (*)(void*);
    using MouseInputCallback = void (*)(EMouseButton, EInputAction, void*);

    Window() = default;
    Window(const Window& other) = delete;
    Window(Window&& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(const Window&& other) = delete;
    ~Window();
    bool Create(const WindowSize& size, const char* title, void* userData);
    void Render();
    void Shutdown();
    void SetLogCallback(LogCallback logCallback);
    void SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback);
    void SetOnRenderWindowDebugCallback(RenderWindowDebugCallback renderWindowDebugCallback);
    void SetOnCloseCallback(CloseWindowCallback closeWindowCallback);
    void SetMouseInputCallback(MouseInputCallback mouseInputCallback);
    WindowSize GetSize() const;
    void* GetWindowImplPtr() const;
    void* GetUserData() const;
    const GraphicLib::FrameBuffer& GetWindowFrameBuffer() const;

private:
    static void _internalSetMouseInputCallback(int button, int action, void* userData);
    void _clear();
    void* _userData{};
    MouseInputCallback _mouseInputCallback{};
};
