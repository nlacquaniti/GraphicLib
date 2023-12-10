#pragma once

enum class EInputAction : int {
    RELEASE,
    PRESS,
    REPEAT,
};

enum class EMouseButton : int {
    LEFT,
    RIGHT,
    MIDDLE,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
};

class InputUtils {
public:
    static const char* MouseInputActionToString(EInputAction inputAction);
    static const char* MouseButtonToString(EMouseButton mouseButton);
};