#include "OpenGLImpl/OpenGLLogSystem.h"

#include <glad/glad.h>
#include <format>
#include <string>

namespace GraphicLib::OpenGLImpl {
namespace {
Logger::Severity OpenGLSeverityToInternal(GLenum openGLSeverity) {
    switch (openGLSeverity) {
        case GL_DEBUG_SEVERITY_HIGH:
            return Logger::Severity::HIGH;
        case GL_DEBUG_SEVERITY_MEDIUM:
            return Logger::Severity::MEDIUM;
        case GL_DEBUG_SEVERITY_LOW:
            return Logger::Severity::LOW;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return Logger::Severity::NOTIFICATION;
        default:
            return Logger::Severity{};
    }
}

const char* DebugSourceToString(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            return "GL_DEBUG_SOURCE_API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "GL_DEBUG_SOURCE_SHADER_COMPILER";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "GL_DEBUG_SOURCE_THIRD_PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "GL_DEBUG_SOURCE_APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:
            return "GL_DEBUG_SOURCE_OTHER";
        default:
            return "GL_UNKOWN";
    }
}

const char* DebugTypeToString(GLenum type) {
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            return "GL_DEBUG_TYPE_ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "GL_DEBUG_TYPE_PORTABILITY";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "GL_DEBUG_TYPE_PERFORMANCE";
        case GL_DEBUG_TYPE_MARKER:
            return "GL_DEBUG_TYPE_MARKER";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return "GL_DEBUG_TYPE_PUSH_GROUP";
        case GL_DEBUG_TYPE_POP_GROUP:
            return "GL_DEBUG_TYPE_POP_GROUP";
        case GL_DEBUG_TYPE_OTHER:
            return "GL_DEBUG_TYPE_OTHER";
        default:
            return "GL_UNKNOWN";
    }
}
} // namespace

void OpenGLLogSystem::_onAttach() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint, GLenum severity, GLsizei, const GLchar* message, const void* userParam) {
            const auto* logSystem = static_cast<const OpenGLLogSystem*>(userParam);

            const std::string& logMessage = std::format("{}: {}", DebugTypeToString(type), message);

            InternalLogger::Message debugMessage{
                Logger::Category::GRAPHIC_API,
                OpenGLSeverityToInternal(severity),
                DebugSourceToString(source),
                logMessage.c_str(),
            };
            logSystem->GetMessageLogCallback()(debugMessage);
        },
        this);
}

void OpenGLLogSystem::_onDetach() {
    glDisable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(nullptr, nullptr);
}
} // namespace GraphicLib::OpenGLImpl
