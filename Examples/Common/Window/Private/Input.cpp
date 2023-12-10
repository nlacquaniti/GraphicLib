#include "Window/Input.h"

const char* InputUtils::MouseInputActionToString(EInputAction inputAction) {
	switch (inputAction)
	{
	case EInputAction::RELEASE:
		return "RELEASE";
	case EInputAction::PRESS:
		return "PRESS";
	case EInputAction::REPEAT:
		return "REPEAT";
	}
	return "ERROR";
}

const char* InputUtils::MouseButtonToString(EMouseButton mouseButton) {
	switch (mouseButton)
	{
	case EMouseButton::LEFT:
		return "LEFT";
	case EMouseButton::RIGHT:
		return "RIGHT";
	case EMouseButton::MIDDLE:
		return "MIDDLE";
	case EMouseButton::BUTTON_3:
		return "BUTTON_3";
	case EMouseButton::BUTTON_4:
		return "BUTTON_4";
	case EMouseButton::BUTTON_5:
		return "BUTTON_5";
	case EMouseButton::BUTTON_6:
		return "BUTTON_6";
	case EMouseButton::BUTTON_7:
		return "BUTTON_7";
	}
	return "ERROR";
}
