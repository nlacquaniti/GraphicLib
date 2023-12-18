#pragma once

#include "Window/Input.h"
#include "Utils/CallbackHandler.h"

struct GLFWwindow;

class InputImpl final {
public:
    static bool Initialise(void* window);
    static void Shutdown();
    static bool IsKeyPressed(EInputKey key);
    static bool IsKeyReleased(EInputKey key);
    static MousePosition GetMousePosition();
    static CallbackHandler<Input::KeyInputCallback> OnKeyInput;

private:
    static bool GetKeyStatus(EInputKey key, int& status);
    static GLFWwindow* _window;
};
