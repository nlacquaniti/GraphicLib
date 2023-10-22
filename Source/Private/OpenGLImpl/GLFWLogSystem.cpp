#include "OpenGLImpl/GLFWLogSystem.h"

#include "OpenGLImpl/glfw.h"
#include <cassert>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
GLFWLogSystem::IExternalLogSystem::MessageLogCallback g_LogMessageCallback{};

const char* glfwErrorToString(int errorCode) {
    switch (errorCode) {
        case GLFW_NOT_INITIALIZED:
            return "GLFW_NOT_INITIALIZED";
        case GLFW_NO_CURRENT_CONTEXT:
            return "GLFW_NO_CURRENT_CONTEXT";
        case GLFW_INVALID_ENUM:
            return "GLFW_INVALID_ENUM";
        case GLFW_INVALID_VALUE:
            return "GLFW_INVALID_VALUE";
        case GLFW_OUT_OF_MEMORY:
            return "GLFW_OUT_OF_MEMORY";
        case GLFW_API_UNAVAILABLE:
            return "GLFW_API_UNAVAILABLE";
        case GLFW_VERSION_UNAVAILABLE:
            return "GLFW_VERSION_UNAVAILABLE";
        case GLFW_PLATFORM_ERROR:
            return "GLFW_PLATFORM_ERROR";
        case GLFW_FORMAT_UNAVAILABLE:
            return "GLFW_FORMAT_UNAVAILABLE";
        case GLFW_NO_WINDOW_CONTEXT:
            return "GLFW_NO_WINDOW_CONTEXT";
        default:
            assert(false);
            return "GLFW_UNKNOWN_ERROR";
    }
}

void glfwErrorCallback(int errorCode, const char* description) {
    InternalLogger::Message message{};
    message.severity = Logger::Severity::HIGH;
    message.source = "GLFW";
    message.type = glfwErrorToString(errorCode);
    message.text = description;
    g_LogMessageCallback(message);
}
} // namespace

void GLFWLogSystem::_onAttach() {
    // Unfortunately glfwSetErrorCallback doesn't allows
    // us to pass a custom pointer on his log callback.
    g_LogMessageCallback = GetMessageLogCallback();
    glfwSetErrorCallback(glfwErrorCallback);
}

void GLFWLogSystem::_onDetach() {
    g_LogMessageCallback = nullptr;
    glfwSetErrorCallback(nullptr);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
