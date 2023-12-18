#include "InputImplUtils.h"

#include <GLFW/glfw3.h>

bool InputImplUtils::InputKeyToGLFWKey(EInputKey inputKey, int& outKey) {
    switch (inputKey) {
        case EInputKey::MOUSE_LEFT:
            outKey = GLFW_MOUSE_BUTTON_1;
            return true;
        case EInputKey::MOUSE_RIGHT:
            outKey = GLFW_MOUSE_BUTTON_2;
            return true;
        case EInputKey::MOUSE_MIDDLE:
            outKey = GLFW_MOUSE_BUTTON_MIDDLE;
            return true;
        case EInputKey::MOUSE_BUTTON_4:
            outKey = GLFW_MOUSE_BUTTON_4;
            return true;
        case EInputKey::MOUSE_BUTTON_5:
            outKey = GLFW_MOUSE_BUTTON_5;
            return true;
        case EInputKey::MOUSE_BUTTON_6:
            outKey = GLFW_MOUSE_BUTTON_6;
            return true;
        case EInputKey::MOUSE_BUTTON_7:
            outKey = GLFW_MOUSE_BUTTON_7;
            return true;
        case EInputKey::SPACE:
            outKey = GLFW_KEY_SPACE;
            return true;
        case EInputKey::APOSTROPHE:
            outKey = GLFW_KEY_APOSTROPHE;
            return true;
        case EInputKey::COMMA:
            outKey = GLFW_KEY_COMMA;
            return true;
        case EInputKey::MINUS:
            outKey = GLFW_KEY_MINUS;
            return true;
        case EInputKey::PERIOD:
            outKey = GLFW_KEY_PERIOD;
            return true;
        case EInputKey::SLASH:
            outKey = GLFW_KEY_SLASH;
            return true;
        case EInputKey::KEY_0:
            outKey = GLFW_KEY_0;
            return true;
        case EInputKey::KEY_1:
            outKey = GLFW_KEY_1;
            return true;
        case EInputKey::KEY_2:
            outKey = GLFW_KEY_2;
            return true;
        case EInputKey::KEY_3:
            outKey = GLFW_KEY_3;
            return true;
        case EInputKey::KEY_4:
            outKey = GLFW_KEY_4;
            return true;
        case EInputKey::KEY_5:
            outKey = GLFW_KEY_5;
            return true;
        case EInputKey::KEY_6:
            outKey = GLFW_KEY_6;
            return true;
        case EInputKey::KEY_7:
            outKey = GLFW_KEY_7;
            return true;
        case EInputKey::KEY_8:
            outKey = GLFW_KEY_8;
            return true;
        case EInputKey::KEY_9:
            outKey = GLFW_KEY_9;
            return true;
        case EInputKey::SEMICOLON:
            outKey = GLFW_KEY_SEMICOLON;
            return true;
        case EInputKey::EQUAL:
            outKey = GLFW_KEY_EQUAL;
            return true;
        case EInputKey::A:
            outKey = GLFW_KEY_A;
            return true;
        case EInputKey::B:
            outKey = GLFW_KEY_B;
            return true;
        case EInputKey::C:
            outKey = GLFW_KEY_C;
            return true;
        case EInputKey::D:
            outKey = GLFW_KEY_D;
            return true;
        case EInputKey::E:
            outKey = GLFW_KEY_E;
            return true;
        case EInputKey::F:
            outKey = GLFW_KEY_F;
            return true;
        case EInputKey::G:
            outKey = GLFW_KEY_G;
            return true;
        case EInputKey::H:
            outKey = GLFW_KEY_H;
            return true;
        case EInputKey::I:
            outKey = GLFW_KEY_I;
            return true;
        case EInputKey::J:
            outKey = GLFW_KEY_J;
            return true;
        case EInputKey::K:
            outKey = GLFW_KEY_K;
            return true;
        case EInputKey::L:
            outKey = GLFW_KEY_L;
            return true;
        case EInputKey::M:
            outKey = GLFW_KEY_M;
            return true;
        case EInputKey::N:
            outKey = GLFW_KEY_N;
            return true;
        case EInputKey::O:
            outKey = GLFW_KEY_O;
            return true;
        case EInputKey::P:
            outKey = GLFW_KEY_P;
            return true;
        case EInputKey::Q:
            outKey = GLFW_KEY_Q;
            return true;
        case EInputKey::R:
            outKey = GLFW_KEY_R;
            return true;
        case EInputKey::S:
            outKey = GLFW_KEY_S;
            return true;
        case EInputKey::T:
            outKey = GLFW_KEY_T;
            return true;
        case EInputKey::U:
            outKey = GLFW_KEY_U;
            return true;
        case EInputKey::V:
            outKey = GLFW_KEY_V;
            return true;
        case EInputKey::W:
            outKey = GLFW_KEY_W;
            return true;
        case EInputKey::X:
            outKey = GLFW_KEY_X;
            return true;
        case EInputKey::Y:
            outKey = GLFW_KEY_Y;
            return true;
        case EInputKey::Z:
            outKey = GLFW_KEY_Z;
            return true;
        case EInputKey::LEFT_BRACKET:
            outKey = GLFW_KEY_LEFT_BRACKET;
            return true;
        case EInputKey::BACKSLASH:
            outKey = GLFW_KEY_BACKSLASH;
            return true;
        case EInputKey::RIGHT_BRACKET:
            outKey = GLFW_KEY_RIGHT_BRACKET;
            return true;
        case EInputKey::GRAVE_ACCENT:
            outKey = GLFW_KEY_GRAVE_ACCENT;
            return true;
        case EInputKey::WORLD_1:
            outKey = GLFW_KEY_WORLD_1;
            return true;
        case EInputKey::WORLD_2:
            outKey = GLFW_KEY_WORLD_2;
            return true;
        case EInputKey::ESCAPE:
            outKey = GLFW_KEY_ESCAPE;
            return true;
        case EInputKey::ENTER:
            outKey = GLFW_KEY_ENTER;
            return true;
        case EInputKey::TAB:
            outKey = GLFW_KEY_TAB;
            return true;
        case EInputKey::BACKSPACE:
            outKey = GLFW_KEY_BACKSPACE;
            return true;
        case EInputKey::INSERT:
            outKey = GLFW_KEY_INSERT;
            return true;
        case EInputKey::DELETE:
            outKey = GLFW_KEY_DELETE;
            return true;
        case EInputKey::RIGHT:
            outKey = GLFW_KEY_RIGHT;
            return true;
        case EInputKey::LEFT:
            outKey = GLFW_KEY_LEFT;
            return true;
        case EInputKey::DOWN:
            outKey = GLFW_KEY_DOWN;
            return true;
        case EInputKey::UP:
            outKey = GLFW_KEY_UP;
            return true;
        case EInputKey::PAGE_UP:
            outKey = GLFW_KEY_PAGE_UP;
            return true;
        case EInputKey::PAGE_DOWN:
            outKey = GLFW_KEY_PAGE_DOWN;
            return true;
        case EInputKey::HOME:
            outKey = GLFW_KEY_HOME;
            return true;
        case EInputKey::END:
            outKey = GLFW_KEY_END;
            return true;
        case EInputKey::CAPS_LOCK:
            outKey = GLFW_KEY_CAPS_LOCK;
            return true;
        case EInputKey::SCROLL_LOCK:
            outKey = GLFW_KEY_SCROLL_LOCK;
            return true;
        case EInputKey::NUM_LOCK:
            outKey = GLFW_KEY_NUM_LOCK;
            return true;
        case EInputKey::PRINT_SCREEN:
            outKey = GLFW_KEY_PRINT_SCREEN;
            return true;
        case EInputKey::PAUSE:
            outKey = GLFW_KEY_PAUSE;
            return true;
        case EInputKey::F1:
            outKey = GLFW_KEY_F1;
            return true;
        case EInputKey::F2:
            outKey = GLFW_KEY_F2;
            return true;
        case EInputKey::F3:
            outKey = GLFW_KEY_F3;
            return true;
        case EInputKey::F4:
            outKey = GLFW_KEY_F4;
            return true;
        case EInputKey::F5:
            outKey = GLFW_KEY_F5;
            return true;
        case EInputKey::F6:
            outKey = GLFW_KEY_F6;
            return true;
        case EInputKey::F7:
            outKey = GLFW_KEY_F7;
            return true;
        case EInputKey::F8:
            outKey = GLFW_KEY_F8;
            return true;
        case EInputKey::F9:
            outKey = GLFW_KEY_F9;
            return true;
        case EInputKey::F10:
            outKey = GLFW_KEY_F10;
            return true;
        case EInputKey::F11:
            outKey = GLFW_KEY_F11;
            return true;
        case EInputKey::F12:
            outKey = GLFW_KEY_F12;
            return true;
        case EInputKey::F13:
            outKey = GLFW_KEY_F13;
            return true;
        case EInputKey::F14:
            outKey = GLFW_KEY_F14;
            return true;
        case EInputKey::F15:
            outKey = GLFW_KEY_F15;
            return true;
        case EInputKey::F16:
            outKey = GLFW_KEY_F16;
            return true;
        case EInputKey::F17:
            outKey = GLFW_KEY_F17;
            return true;
        case EInputKey::F18:
            outKey = GLFW_KEY_F18;
            return true;
        case EInputKey::F19:
            outKey = GLFW_KEY_F19;
            return true;
        case EInputKey::F20:
            outKey = GLFW_KEY_F20;
            return true;
        case EInputKey::F21:
            outKey = GLFW_KEY_F21;
            return true;
        case EInputKey::F22:
            outKey = GLFW_KEY_F22;
            return true;
        case EInputKey::F23:
            outKey = GLFW_KEY_F23;
            return true;
        case EInputKey::F24:
            outKey = GLFW_KEY_F24;
            return true;
        case EInputKey::F25:
            outKey = GLFW_KEY_F25;
            return true;
        case EInputKey::KP_0:
            outKey = GLFW_KEY_KP_0;
            return true;
        case EInputKey::KP_1:
            outKey = GLFW_KEY_KP_1;
            return true;
        case EInputKey::KP_2:
            outKey = GLFW_KEY_KP_2;
            return true;
        case EInputKey::KP_3:
            outKey = GLFW_KEY_KP_3;
            return true;
        case EInputKey::KP_4:
            outKey = GLFW_KEY_KP_4;
            return true;
        case EInputKey::KP_5:
            outKey = GLFW_KEY_KP_5;
            return true;
        case EInputKey::KP_6:
            outKey = GLFW_KEY_KP_6;
            return true;
        case EInputKey::KP_7:
            outKey = GLFW_KEY_KP_7;
            return true;
        case EInputKey::KP_8:
            outKey = GLFW_KEY_KP_8;
            return true;
        case EInputKey::KP_9:
            outKey = GLFW_KEY_KP_9;
            return true;
        case EInputKey::KP_DECIMAL:
            outKey = GLFW_KEY_KP_DECIMAL;
            return true;
        case EInputKey::KP_DIVIDE:
            outKey = GLFW_KEY_KP_DIVIDE;
            return true;
        case EInputKey::KP_MULTIPLY:
            outKey = GLFW_KEY_KP_MULTIPLY;
            return true;
        case EInputKey::KP_SUBTRACT:
            outKey = GLFW_KEY_KP_SUBTRACT;
            return true;
        case EInputKey::KP_ADD:
            outKey = GLFW_KEY_KP_ADD;
            return true;
        case EInputKey::KP_ENTER:
            outKey = GLFW_KEY_KP_ENTER;
            return true;
        case EInputKey::KP_EQUAL:
            outKey = GLFW_KEY_KP_EQUAL;
            return true;
        case EInputKey::LEFT_SHIFT:
            outKey = GLFW_KEY_LEFT_SHIFT;
            return true;
        case EInputKey::LEFT_CONTROL:
            outKey = GLFW_KEY_LEFT_CONTROL;
            return true;
        case EInputKey::LEFT_ALT:
            outKey = GLFW_KEY_LEFT_ALT;
            return true;
        case EInputKey::LEFT_SUPER:
            outKey = GLFW_KEY_LEFT_SUPER;
            return true;
        case EInputKey::RIGHT_SHIFT:
            outKey = GLFW_KEY_RIGHT_SHIFT;
            return true;
        case EInputKey::RIGHT_CONTROL:
            outKey = GLFW_KEY_RIGHT_CONTROL;
            return true;
        case EInputKey::RIGHT_ALT:
            outKey = GLFW_KEY_RIGHT_ALT;
            return true;
        case EInputKey::RIGHT_SUPER:
            outKey = GLFW_KEY_RIGHT_SUPER;
            return true;
        case EInputKey::MENU:
            outKey = GLFW_KEY_MENU;
            return true;
        default:
            break;
    }
    return false;
}

bool InputImplUtils::GLFWKeyToInputKey(int glfwKey, EInputKey& outKey) {
    switch (glfwKey) {
        case GLFW_MOUSE_BUTTON_1:
            outKey = EInputKey::MOUSE_LEFT;
            return true;
        case GLFW_MOUSE_BUTTON_2:
            outKey = EInputKey::MOUSE_RIGHT;
            return true;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            outKey = EInputKey::MOUSE_MIDDLE;
            return true;
        case GLFW_MOUSE_BUTTON_4:
            outKey = EInputKey::MOUSE_BUTTON_4;
            return true;
        case GLFW_MOUSE_BUTTON_5:
            outKey = EInputKey::MOUSE_BUTTON_5;
            return true;
        case GLFW_MOUSE_BUTTON_6:
            outKey = EInputKey::MOUSE_BUTTON_6;
            return true;
        case GLFW_MOUSE_BUTTON_7:
            outKey = EInputKey::MOUSE_BUTTON_7;
            return true;
        case GLFW_KEY_SPACE:
            outKey = EInputKey::SPACE;
            return true;
        case GLFW_KEY_APOSTROPHE:
            outKey = EInputKey::APOSTROPHE;
            return true;
        case GLFW_KEY_COMMA:
            outKey = EInputKey::COMMA;
            return true;
        case GLFW_KEY_MINUS:
            outKey = EInputKey::MINUS;
            return true;
        case GLFW_KEY_PERIOD:
            outKey = EInputKey::PERIOD;
            return true;
        case GLFW_KEY_SLASH:
            outKey = EInputKey::SLASH;
            return true;
        case GLFW_KEY_0:
            outKey = EInputKey::KEY_0;
            return true;
        case GLFW_KEY_1:
            outKey = EInputKey::KEY_1;
            return true;
        case GLFW_KEY_2:
            outKey = EInputKey::KEY_2;
            return true;
        case GLFW_KEY_3:
            outKey = EInputKey::KEY_3;
            return true;
        case GLFW_KEY_4:
            outKey = EInputKey::KEY_4;
            return true;
        case GLFW_KEY_5:
            outKey = EInputKey::KEY_5;
            return true;
        case GLFW_KEY_6:
            outKey = EInputKey::KEY_6;
            return true;
        case GLFW_KEY_7:
            outKey = EInputKey::KEY_7;
            return true;
        case GLFW_KEY_8:
            outKey = EInputKey::KEY_8;
            return true;
        case GLFW_KEY_9:
            outKey = EInputKey::KEY_9;
            return true;
        case GLFW_KEY_SEMICOLON:
            outKey = EInputKey::SEMICOLON;
            return true;
        case GLFW_KEY_EQUAL:
            outKey = EInputKey::EQUAL;
            return true;
        case GLFW_KEY_A:
            outKey = EInputKey::A;
            return true;
        case GLFW_KEY_B:
            outKey = EInputKey::B;
            return true;
        case GLFW_KEY_C:
            outKey = EInputKey::C;
            return true;
        case GLFW_KEY_D:
            outKey = EInputKey::D;
            return true;
        case GLFW_KEY_E:
            outKey = EInputKey::E;
            return true;
        case GLFW_KEY_F:
            outKey = EInputKey::F;
            return true;
        case GLFW_KEY_G:
            outKey = EInputKey::G;
            return true;
        case GLFW_KEY_H:
            outKey = EInputKey::H;
            return true;
        case GLFW_KEY_I:
            outKey = EInputKey::I;
            return true;
        case GLFW_KEY_J:
            outKey = EInputKey::J;
            return true;
        case GLFW_KEY_K:
            outKey = EInputKey::K;
            return true;
        case GLFW_KEY_L:
            outKey = EInputKey::L;
            return true;
        case GLFW_KEY_M:
            outKey = EInputKey::M;
            return true;
        case GLFW_KEY_N:
            outKey = EInputKey::N;
            return true;
        case GLFW_KEY_O:
            outKey = EInputKey::O;
            return true;
        case GLFW_KEY_P:
            outKey = EInputKey::P;
            return true;
        case GLFW_KEY_Q:
            outKey = EInputKey::Q;
            return true;
        case GLFW_KEY_R:
            outKey = EInputKey::R;
            return true;
        case GLFW_KEY_S:
            outKey = EInputKey::S;
            return true;
        case GLFW_KEY_T:
            outKey = EInputKey::T;
            return true;
        case GLFW_KEY_U:
            outKey = EInputKey::U;
            return true;
        case GLFW_KEY_V:
            outKey = EInputKey::V;
            return true;
        case GLFW_KEY_W:
            outKey = EInputKey::W;
            return true;
        case GLFW_KEY_X:
            outKey = EInputKey::X;
            return true;
        case GLFW_KEY_Y:
            outKey = EInputKey::Y;
            return true;
        case GLFW_KEY_Z:
            outKey = EInputKey::Z;
            return true;
        case GLFW_KEY_LEFT_BRACKET:
            outKey = EInputKey::LEFT_BRACKET;
            return true;
        case GLFW_KEY_BACKSLASH:
            outKey = EInputKey::BACKSLASH;
            return true;
        case GLFW_KEY_RIGHT_BRACKET:
            outKey = EInputKey::RIGHT_BRACKET;
            return true;
        case GLFW_KEY_GRAVE_ACCENT:
            outKey = EInputKey::GRAVE_ACCENT;
            return true;
        case GLFW_KEY_WORLD_1:
            outKey = EInputKey::WORLD_1;
            return true;
        case GLFW_KEY_WORLD_2:
            outKey = EInputKey::WORLD_2;
            return true;
        case GLFW_KEY_ESCAPE:
            outKey = EInputKey::ESCAPE;
            return true;
        case GLFW_KEY_ENTER:
            outKey = EInputKey::ENTER;
            return true;
        case GLFW_KEY_TAB:
            outKey = EInputKey::TAB;
            return true;
        case GLFW_KEY_BACKSPACE:
            outKey = EInputKey::BACKSPACE;
            return true;
        case GLFW_KEY_INSERT:
            outKey = EInputKey::INSERT;
            return true;
        case GLFW_KEY_DELETE:
            outKey = EInputKey::DELETE;
            return true;
        case GLFW_KEY_RIGHT:
            outKey = EInputKey::RIGHT;
            return true;
        case GLFW_KEY_LEFT:
            outKey = EInputKey::LEFT;
            return true;
        case GLFW_KEY_DOWN:
            outKey = EInputKey::DOWN;
            return true;
        case GLFW_KEY_UP:
            outKey = EInputKey::UP;
            return true;
        case GLFW_KEY_PAGE_UP:
            outKey = EInputKey::PAGE_UP;
            return true;
        case GLFW_KEY_PAGE_DOWN:
            outKey = EInputKey::PAGE_DOWN;
            return true;
        case GLFW_KEY_HOME:
            outKey = EInputKey::HOME;
            return true;
        case GLFW_KEY_END:
            outKey = EInputKey::END;
            return true;
        case GLFW_KEY_CAPS_LOCK:
            outKey = EInputKey::CAPS_LOCK;
            return true;
        case GLFW_KEY_SCROLL_LOCK:
            outKey = EInputKey::SCROLL_LOCK;
            return true;
        case GLFW_KEY_NUM_LOCK:
            outKey = EInputKey::NUM_LOCK;
            return true;
        case GLFW_KEY_PRINT_SCREEN:
            outKey = EInputKey::PRINT_SCREEN;
            return true;
        case GLFW_KEY_PAUSE:
            outKey = EInputKey::PAUSE;
            return true;
        case GLFW_KEY_F1:
            outKey = EInputKey::F1;
            return true;
        case GLFW_KEY_F2:
            outKey = EInputKey::F2;
            return true;
        case GLFW_KEY_F3:
            outKey = EInputKey::F3;
            return true;
        case GLFW_KEY_F4:
            outKey = EInputKey::F4;
            return true;
        case GLFW_KEY_F5:
            outKey = EInputKey::F5;
            return true;
        case GLFW_KEY_F6:
            outKey = EInputKey::F6;
            return true;
        case GLFW_KEY_F7:
            outKey = EInputKey::F7;
            return true;
        case GLFW_KEY_F8:
            outKey = EInputKey::F8;
            return true;
        case GLFW_KEY_F9:
            outKey = EInputKey::F9;
            return true;
        case GLFW_KEY_F10:
            outKey = EInputKey::F10;
            return true;
        case GLFW_KEY_F11:
            outKey = EInputKey::F11;
            return true;
        case GLFW_KEY_F12:
            outKey = EInputKey::F12;
            return true;
        case GLFW_KEY_F13:
            outKey = EInputKey::F13;
            return true;
        case GLFW_KEY_F14:
            outKey = EInputKey::F14;
            return true;
        case GLFW_KEY_F15:
            outKey = EInputKey::F15;
            return true;
        case GLFW_KEY_F16:
            outKey = EInputKey::F16;
            return true;
        case GLFW_KEY_F17:
            outKey = EInputKey::F17;
            return true;
        case GLFW_KEY_F18:
            outKey = EInputKey::F18;
            return true;
        case GLFW_KEY_F19:
            outKey = EInputKey::F19;
            return true;
        case GLFW_KEY_F20:
            outKey = EInputKey::F20;
            return true;
        case GLFW_KEY_F21:
            outKey = EInputKey::F21;
            return true;
        case GLFW_KEY_F22:
            outKey = EInputKey::F22;
            return true;
        case GLFW_KEY_F23:
            outKey = EInputKey::F23;
            return true;
        case GLFW_KEY_F24:
            outKey = EInputKey::F24;
            return true;
        case GLFW_KEY_F25:
            outKey = EInputKey::F25;
            return true;
        case GLFW_KEY_KP_0:
            outKey = EInputKey::KP_0;
            return true;
        case GLFW_KEY_KP_1:
            outKey = EInputKey::KP_1;
            return true;
        case GLFW_KEY_KP_2:
            outKey = EInputKey::KP_2;
            return true;
        case GLFW_KEY_KP_3:
            outKey = EInputKey::KP_3;
            return true;
        case GLFW_KEY_KP_4:
            outKey = EInputKey::KP_4;
            return true;
        case GLFW_KEY_KP_5:
            outKey = EInputKey::KP_5;
            return true;
        case GLFW_KEY_KP_6:
            outKey = EInputKey::KP_6;
            return true;
        case GLFW_KEY_KP_7:
            outKey = EInputKey::KP_7;
            return true;
        case GLFW_KEY_KP_8:
            outKey = EInputKey::KP_8;
            return true;
        case GLFW_KEY_KP_9:
            outKey = EInputKey::KP_9;
            return true;
        case GLFW_KEY_KP_DECIMAL:
            outKey = EInputKey::KP_DECIMAL;
            return true;
        case GLFW_KEY_KP_DIVIDE:
            outKey = EInputKey::KP_DIVIDE;
            return true;
        case GLFW_KEY_KP_MULTIPLY:
            outKey = EInputKey::KP_MULTIPLY;
            return true;
        case GLFW_KEY_KP_SUBTRACT:
            outKey = EInputKey::KP_SUBTRACT;
            return true;
        case GLFW_KEY_KP_ADD:
            outKey = EInputKey::KP_ADD;
            return true;
        case GLFW_KEY_KP_ENTER:
            outKey = EInputKey::KP_ENTER;
            return true;
        case GLFW_KEY_KP_EQUAL:
            outKey = EInputKey::KP_EQUAL;
            return true;
        case GLFW_KEY_LEFT_SHIFT:
            outKey = EInputKey::LEFT_SHIFT;
            return true;
        case GLFW_KEY_LEFT_CONTROL:
            outKey = EInputKey::LEFT_CONTROL;
            return true;
        case GLFW_KEY_LEFT_ALT:
            outKey = EInputKey::LEFT_ALT;
            return true;
        case GLFW_KEY_LEFT_SUPER:
            outKey = EInputKey::LEFT_SUPER;
            return true;
        case GLFW_KEY_RIGHT_SHIFT:
            outKey = EInputKey::RIGHT_SHIFT;
            return true;
        case GLFW_KEY_RIGHT_CONTROL:
            outKey = EInputKey::RIGHT_CONTROL;
            return true;
        case GLFW_KEY_RIGHT_ALT:
            outKey = EInputKey::RIGHT_ALT;
            return true;
        case GLFW_KEY_RIGHT_SUPER:
            outKey = EInputKey::RIGHT_SUPER;
            return true;
        case GLFW_KEY_MENU:
            outKey = EInputKey::MENU;
            return true;
        default:
            break;
    }
    return false;
}

bool InputImplUtils::GLFWActionToInputAction(int glfwAction, EInputAction& outAction) {
    switch (glfwAction) {
        case GLFW_RELEASE:
            outAction = EInputAction::RELEASE;
            return true;
        case GLFW_PRESS:
            outAction = EInputAction::PRESS;
            return true;
        case GLFW_REPEAT:
            outAction = EInputAction::REPEAT;
            return true;
        default:
            break;
    }
    return false;
}
