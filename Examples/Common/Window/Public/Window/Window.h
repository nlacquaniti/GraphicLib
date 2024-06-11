#pragma once

namespace GraphicLib {
class FrameBuffer;
};

class Window {
public:
    struct Size {
        int Width{};
        int Height{};
    };

    struct Resolution {
        int Width{};
        int Height{};
    };

    using LogCallback = void (*)(const char*, void*);
    using UpdateCallback = void (*)(float, void*);
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
    [[nodiscard]] Size GetSize() const;
    [[nodiscard]] Resolution GetResolution() const;
    [[nodiscard]] void* GetWindowImplPtr() const;
    [[nodiscard]] void* GetUserData() const;
    [[nodiscard]] const GraphicLib::FrameBuffer& GetWindowFrameBuffer() const;

private:
    void _clear();
    void* _userData{};
};
