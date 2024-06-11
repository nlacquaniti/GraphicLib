#include "WindowImpl.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

#include <GraphicLib/Texture.h>

CallbackHandler<void (*)(const char*, void*)> WindowImpl::OnDebugLog{};
CallbackHandler<void (*)(float, void*)> WindowImpl::OnUpdate{};
CallbackHandler<void (*)(void*)> WindowImpl::OnRenderDraw{};
CallbackHandler<void (*)(void*)> WindowImpl::OnRenderDrawDebug{};
CallbackHandler<void (*)(void*)> WindowImpl::OnWindowClosed{};
GLFWwindow* WindowImpl::_window{};
GraphicLib::FrameBuffer WindowImpl::_windowFrameBuffer{};

bool WindowImpl::Create(const char* title) {
    if (title == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window without a title");
        return false;
    }

    if (!glfwInit()) {
        _clear();
        return false;
    }

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    _window = glfwCreateWindow(mode->width, mode->height, title, nullptr, nullptr);
    if (_window == nullptr) {
        _clear();
        return false;
    }

    glfwSetWindowCloseCallback(_window, _onWindowClosed);
    glfwSetWindowSizeCallback(_window, _onSetWindowSize);

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    io.FontGlobalScale = 1.5f;
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // FrameBuffer creation.
    _windowFrameBuffer.Initialise();
    _windowFrameBuffer.Bind();

    // Framebuffer config.
    _windowFrameBuffer.GetTexture().Initialise();
    _windowFrameBuffer.GetRenderBuffer().Initialise();
    _setFrameBufferConfiguration();

    // Finalise FrameBuffer.
    _windowFrameBuffer.Set();
    _windowFrameBuffer.Unbind();

    return true;
}

void WindowImpl::Update() {
    if (glfwWindowShouldClose(_window)) {
        OnWindowClosed.Invoke();
        _clear();
        return;
    }

    // Calculate delta time.
    static auto previousTime = static_cast<float>(glfwGetTime());
    const auto currentTime = static_cast<float>(glfwGetTime());
    const auto deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    glfwPollEvents();

    OnUpdate.Invoke(deltaTime);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    _setFrameBufferConfiguration();
    _windowFrameBuffer.Bind();
    int width, height;
    GetSize(width, height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    OnRenderDraw.Invoke();
    _windowFrameBuffer.Unbind();

    OnRenderDrawDebug.Invoke();

    ImGui::Render();
    glfwGetFramebufferSize(_window, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Update additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(_window);
}

void WindowImpl::Shutdown() {
    if (_window != nullptr) {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
}

void WindowImpl::GetSize(int& width, int& height) {
    glfwGetWindowSize(_window, &width, &height);
}

void WindowImpl::GetResolution(int& width, int& height) {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    width = mode->width;
    height = mode->height;
}

GLFWwindow* WindowImpl::GetWindowPtr() {
    return _window;
}

const GraphicLib::FrameBuffer& WindowImpl::GetFrameBuffer() {
    return _windowFrameBuffer;
}

void WindowImpl::_clear() {
    if (_window != nullptr) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(_window);
        _window = nullptr;
        glfwTerminate();
    }

    OnDebugLog.Clear();
    OnUpdate.Clear();
    OnRenderDraw.Clear();
    OnRenderDrawDebug.Clear();
    OnWindowClosed.Clear();
}

void WindowImpl::_onWindowClosed(GLFWwindow*) {
    Shutdown();
}

void WindowImpl::_onSetWindowSize(GLFWwindow*, int width, int height) {
    Update();
}

void WindowImpl::_invokeLogCallback(const char* message) {
    OnDebugLog.Invoke(message);
}

void WindowImpl::_setFrameBufferConfiguration() {
    int windowWidth, windowHeight;
    GetSize(windowWidth, windowHeight);

    // FrameBuffer texture.
    GraphicLib::TextureData frameBufferTextureData{};
    frameBufferTextureData.Parameters = {
        {GraphicLib::ETextureParamName::MIN_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
        {GraphicLib::ETextureParamName::MAG_FILTER, GraphicLib::ETextureParamValue::FILTER_LIEAR},
    };
    frameBufferTextureData.Name = "FramebufferTexture";
    frameBufferTextureData.Width = windowWidth;
    frameBufferTextureData.Height = windowHeight;
    frameBufferTextureData.Type = GraphicLib::ETextureType::TEXTURE_2D;
    frameBufferTextureData.Channel = GraphicLib::ETextureChannel::RGBA;
    frameBufferTextureData.Format = GraphicLib::ETextureFormat::RGBA;
    frameBufferTextureData.DataType = GraphicLib::ETextureDataType::UNSIGNED_BYTE;

    _windowFrameBuffer.GetTexture().Set(std::move(frameBufferTextureData));

    // Frame buffer render buffer creation.
    _windowFrameBuffer.GetRenderBuffer().Bind();
    _windowFrameBuffer.GetRenderBuffer().Set({GraphicLib::ERenderBufferFormat::DEPTH24, windowWidth, windowHeight});
}
