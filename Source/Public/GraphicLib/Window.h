#pragma once

#include "DLL_API.h"

namespace GraphicLib {
struct DLL_API WindowSize {
    int Width{};
    int Height{};
};

class DLL_API Window final {
public:
    using CloseWindowCallback = void (*)(void*);
    using RenderWindowCallback = void (*)(void*);

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
    WindowSize GetSize() const;

private:
    void _clear();
    void* _userData{};
};
} // namespace GraphicLib
