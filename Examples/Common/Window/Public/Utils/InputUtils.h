#pragma once

#include "Window/Input.h"

class InputUtils final {
public:
    static const char* MouseInputActionToString(EInputAction inputAction);
    static const char* InputKeyToString(EInputKey inputKey);
    static bool IsMouseInput(EInputKey key);
};
