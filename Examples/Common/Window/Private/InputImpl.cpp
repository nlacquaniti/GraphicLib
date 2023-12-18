#include "InputImpl.h"

#include "InputImplUtils.h"
#include "Utils/InputUtils.h"

#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>

CallbackHandler<Input::KeyInputCallback> InputImpl::OnKeyInput{};
GLFWwindow* InputImpl::_window{};

bool InputImpl::Initialise(void* window) {
    _window = static_cast<GLFWwindow*>(window);
    glfwSetKeyCallback(_window, [](GLFWwindow* window, int glfwKey, int glfwScancode, int glfwAction, int glfwMods) {
        ImGui_ImplGlfw_KeyCallback(window, glfwKey, glfwScancode, glfwAction, glfwMods);
        EInputKey key{};
        EInputAction action{};
        if (!InputImplUtils::GLFWKeyToInputKey(glfwKey, key) || !InputImplUtils::GLFWActionToInputAction(glfwAction, action)) {
            return;
        }

        InputImpl::OnKeyInput.Invoke(key, action);
    });
    return _window != nullptr;
}

void InputImpl::Shutdown() {
    OnKeyInput.Clear();
    if (_window != nullptr) {
        glfwSetKeyCallback(_window, nullptr);
        _window = nullptr;
    }
}

bool InputImpl::IsKeyPressed(EInputKey key) {
    int keyStatus{};
    return GetKeyStatus(key, keyStatus) && keyStatus == GLFW_PRESS;
}

bool InputImpl::IsKeyReleased(EInputKey key) {
    int keyStatus{};
    return GetKeyStatus(key, keyStatus) && keyStatus == GLFW_RELEASE;
}

MousePosition InputImpl::GetMousePosition() {
    if (_window == nullptr) {
        return {};
    }
    MousePosition mousePosition{};
    glfwGetCursorPos(_window, &mousePosition.X, &mousePosition.Y);
    return mousePosition;
}

bool InputImpl::GetKeyStatus(EInputKey key, int& status) {
    if (_window == nullptr) {
        return false;
    }

    int glfwKey{};
    if (!InputImplUtils::InputKeyToGLFWKey(key, glfwKey)) {
        return false;
    }

    if (InputUtils::IsMouseInput(key)) {
        status = glfwGetMouseButton(_window, glfwKey);
    } else {
        status = glfwGetKey(_window, glfwKey);
    }

    return true;
}
