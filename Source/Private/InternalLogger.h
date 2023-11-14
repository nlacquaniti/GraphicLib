#pragma once

#include "GraphicLib/Logger.h"

#include <memory>
#include <unordered_map>

namespace GraphicLib {
#define STRINGIFY(str) #str
#define LOG_SOURCE() STRINGIFY(__FILE__) STRINGIFY(__func__) STRINGIFY(__LINE__)
#define LOG_INTERNAL_NOTIFICATION(message) InternalLogger::Get().LogInternalNotification(LOG_SOURCE(), message)
#define LOG_INTERNAL_ERROR(message) InternalLogger::Get().LogInternalError(LOG_SOURCE(), message)

class IExternalLogSystem;
class InternalLogger final {
public:
    struct Message {
        Logger::Severity severity{};
        const char* source{};
        const char* text{};
    };
    static InternalLogger& Get();
    void SetCallback(Logger::MessageCallback callback, const void* userData);
    void SetSeverity(Logger::Severity severity);
    void LogMessage(const Message& message);
    void LogInternalNotification(const char* source, const char* text);
    void LogInternalError(const char* source, const char* text);
    std::size_t AttachExternalLogSystem(std::unique_ptr<IExternalLogSystem> externalLogSystem);
    void DetachExternalLogSystem(std::size_t id);

private:
    static InternalLogger* _instance;
    std::unordered_map<std::size_t, std::unique_ptr<IExternalLogSystem>> _externalLogSystems{};
    Logger::Severity _severity{};
    Logger::MessageCallback _callback{};
    const void* _userData{};
};
} // namespace GraphicLib
