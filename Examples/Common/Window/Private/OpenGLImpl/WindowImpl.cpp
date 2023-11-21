#include "WindowImpl.h"

#include "glad.h"
#define GLFW_INCLUDE_NONE
#include "glfw.h"

#include "imgui/backends/imgui_impl_opengl3.h"
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui.h>

void* WindowImpl::_userData{};
WindowImpl::OnWindowClosedCallback WindowImpl::_onWindowClosedCallback{};
WindowImpl::OnRenderCallback WindowImpl::_onRenderCallback{};
WindowImpl::OnRenderDebugCallback WindowImpl::_onRenderDebugCallback{};
WindowImpl::OnWindowLogCallback WindowImpl::_onWindowLogCallback{};
GLFWwindow* WindowImpl::_window{};

bool WindowImpl::Create(int width, int height, const char* title, void* userData) {
    if (width < 1 || height < 1) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window with either width or height with 0 or less value");
        return false;
    }

    if (title == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window without a title");
        return false;
    }

    _userData = userData;

    if (!glfwInit()) {
        _clear();
        return false;
    }

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (_window == nullptr) {
        _clear();
        return false;
    }

    glfwSetWindowCloseCallback(_window, _onWindowClosed);
    glfwSetKeyCallback(_window, _onKeyPressed);
    glfwSetWindowSizeCallback(_window, _onSetWindowSize);

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
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

    return true;
}

void WindowImpl::Render() {
    if (_window == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Render: GLFWwindow is null");
        return;
    }

    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (_onRenderDebugCallback != nullptr) {
        _onRenderDebugCallback(_userData);
    }
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);

    if (_onRenderCallback != nullptr) {
        _onRenderCallback(_userData);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
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
    _clear();
}

void WindowImpl::SetRenderCallback(OnRenderCallback onRenderCallback) {
    _onRenderCallback = onRenderCallback;
}

void WindowImpl::SetRenderDebugCallback(OnRenderDebugCallback onRenderDebugCallback) {
    _onRenderDebugCallback = onRenderDebugCallback;
}

void WindowImpl::SetWindowClosedCallback(OnWindowClosedCallback onWindowClosedCallback) {
    _onWindowClosedCallback = onWindowClosedCallback;
}

void WindowImpl::SetLogCallback(OnWindowLogCallback onWindowLogCallback) {
    _onWindowLogCallback = onWindowLogCallback;
}

void WindowImpl::GetSize(int& width, int& height) {
    glfwGetWindowSize(_window, &width, &height);
}

GLFWwindow* WindowImpl::GetWindowPtr() {
    return _window;
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

    _userData = nullptr;
    _onWindowClosedCallback = nullptr;
    _onRenderCallback = nullptr;
    _onRenderDebugCallback = nullptr;
    _onWindowLogCallback = nullptr;
}

void WindowImpl::_onWindowClosed(GLFWwindow*) {
    if (_onWindowClosedCallback != nullptr) {
        _onWindowClosedCallback(_userData);
    }
}

void WindowImpl::_onKeyPressed(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        _onWindowClosed(window);
    }
}

void WindowImpl::_onSetWindowSize(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
    Render();
}

void WindowImpl::_invokeLogCallback(const char* message) {
    if (_onWindowLogCallback != nullptr) {
        _onWindowLogCallback(message);
    }
}
