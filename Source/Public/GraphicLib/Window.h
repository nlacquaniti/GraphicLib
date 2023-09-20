#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Window {
public:
    using CloseWindowCallback = void (*)(void*);
    using RenderWindowCallback = void(*)(void*);
    virtual ~Window() = default;
    void Initialise();
    void Render();
    void Shutdown();
    void SetOnCloseCallback(CloseWindowCallback closeWindowCallback, void* userData);
    void SetOnRenderWindowCallback(RenderWindowCallback renderWindowCallback, void* userData);
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

protected:
    Window() = default;

private:
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    virtual void _initialise() = 0;
    virtual void _render() = 0;
    virtual void _shutdown() = 0;
    virtual void _setOnCloseCallback(CloseWindowCallback closeWindowCallback, void* userData) = 0;
    virtual void _setOnRenderWindowCallback(RenderWindowCallback renderWindowCallback, void* userData) = 0;
    virtual unsigned int _getWidth() const = 0;
    virtual unsigned int _getHeight() const = 0;
};

extern "C" DLL_API Window* CreateWindow(unsigned int width, unsigned int height, const char* title);
} // namespace GraphicLib
