#pragma once
#include "Window/Input.h"

class InputImplUtils {
public:
	static bool InputKeyToGLFWKey(EInputKey inputKey, int& outKey);
	static bool GLFWKeyToInputKey(int glfwKey, EInputKey& outKey);
	static bool GLFWActionToInputAction(int glfwAction, EInputAction& outAction);
};