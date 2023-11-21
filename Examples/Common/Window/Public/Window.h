#pragma once

struct WindowSize {
    int Width{};
    int Height{};
};

class Window final {
public:
    using CloseWindowCallback = void (*)(void*);
    using RenderWindowCallback = void (*)(void*);
    using RenderWindowDebugCallback = void (*)(void*);
    using LogCallback = void(*)(const char*);

    Window() = default;
    Window(const Window& other) = delete;
    Window(Window&& other) = delete;
    Window& operator=(const Window& other) = delete;
    Window& operator=(const Window&& other) = delete;
    ~Window();
    bool Create(const WindowSize& size, const char* title, void* userData);
    void Render();
    void Shutdown();
    void SetOnCloseCallback(CloseWindowCallback closeWindowCallback);
    void SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback);
    void SetOnRenderWindowDebugCallback(RenderWindowDebugCallback renderWindowDebugCallback);
    void SetLogCallback(LogCallback logCallback);
    WindowSize GetSize() const;
    void* GetWindowImplPtr() const;

private:
    void _clear();
    void* _userData{};
};
