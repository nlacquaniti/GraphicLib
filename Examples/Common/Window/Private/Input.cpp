#include "Window/Input.h"

#include "InputImpl.h"
#include "Window/Window.h"

Input::~Input() {
    Shutdown();
}

bool Input::Initialise(const Window& window) {
    return InputImpl::Initialise(window.GetWindowImplPtr());
}

void Input::Shutdown() {
    InputImpl::Shutdown();
}

void Input::SetKeyInputCallback(KeyInputCallback keyCallback, void* userData) {
    InputImpl::OnKeyInput.Set(keyCallback, userData);
}

bool Input::IsKeyPressed(EInputKey key) {
    return InputImpl::IsKeyPressed(key);
}

bool Input::IsKeyReleased(EInputKey key) {
    return InputImpl::IsKeyReleased(key);
}

MousePosition Input::GetMousePosition() {
    return InputImpl::GetMousePosition();
}
