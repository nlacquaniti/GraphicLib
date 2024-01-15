#pragma once

namespace GraphicLib {
class FrameBuffer;
};

struct WindowSize {
    int Width{};
    int Height{};
};

class Window {
public:
    using LogCallback = void (*)(const char*, void*);
    using UpdateCallback = void(*)(float, void*);
    using RenderWindowCallback = void (*)(void*);
    using RenderWindowDebugCallback = void (*)(void*);
    using CloseWindowCallback = void (*)(void*);

    Window() = default;
    Window(const Window& other) = delete;
    Window(Window&& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(const Window&& other) = delete;
    ~Window();
    bool Initialise(const char* title, void* userData);
    void Update();
    void Shutdown();
    void SetLogCallback(LogCallback logCallback);
    void SetUpdateCallback(UpdateCallback updateCallback);
    void SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback);
    void SetOnRenderWindowDebugCallback(RenderWindowDebugCallback renderWindowDebugCallback);
    void SetOnCloseCallback(CloseWindowCallback closeWindowCallback);
    WindowSize GetSize() const;
    void* GetWindowImplPtr() const;
    void* GetUserData() const;
    const GraphicLib::FrameBuffer& GetWindowFrameBuffer() const;

private:
    void _clear();
    void* _userData{};
};
