#include "WindowImpl.h"

#include "glad.h"
#define GLFW_INCLUDE_NONE
#include "glfw.h"

#include "imgui/backends/imgui_impl_opengl3.h"
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/imgui.h>

WindowCallbackHandler<void (*)(const char*, void*)> WindowImpl::OnDebugLog{};
WindowCallbackHandler<void (*)(void*)> WindowImpl::OnRenderDraw{};
WindowCallbackHandler<void (*)(void*)> WindowImpl::OnRenderDrawDebug{};
WindowCallbackHandler<void (*)(void*)> WindowImpl::OnWindowClosed{};
WindowCallbackHandler<void (*)(int, int, void*)> WindowImpl::OnMouseInput{};
GLFWwindow* WindowImpl::_window{};

bool WindowImpl::Create(int width, int height, const char* title) {
    if (width < 1 || height < 1) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window with either width or height with 0 or less value");
        return false;
    }

    if (title == nullptr) {
        _invokeLogCallback("OpenGLImpl::WindowImpl::Create: Cannot create a window without a title");
        return false;
    }

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
    glfwSetWindowSizeCallback(_window, _onSetWindowSize);
    glfwSetKeyCallback(_window, _onKeyPressed);
    glfwSetMouseButtonCallback(_window, _onMouseButtonCallback);

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
    gladLoadGL();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

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
    if (OnRenderDrawDebug.Callback != nullptr) {
        OnRenderDrawDebug.Callback(OnRenderDrawDebug.UserData);
    }
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (OnRenderDraw.Callback != nullptr) {
        OnRenderDraw.Callback(OnRenderDraw.UserData);
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
}

void WindowImpl::_onWindowClosed(GLFWwindow*) {
    if (OnWindowClosed.Callback !=nullptr) {
        OnWindowClosed.Callback(OnWindowClosed.UserData);
    }
}

void WindowImpl::_onKeyPressed(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        _onWindowClosed(window);
    }
}

void WindowImpl::_onMouseButtonCallback(GLFWwindow* window, int button, int action, int) {
    if (OnMouseInput.Callback != nullptr) {
        OnMouseInput.Callback(button, action, OnMouseInput.UserData);
    }
}

void WindowImpl::_onSetWindowSize(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
    Render();
}

void WindowImpl::_invokeLogCallback(const char* message) {
    if (OnDebugLog.Callback != nullptr) {
        OnDebugLog.Callback(message, OnDebugLog.UserData);
    }
}
