#pragma once

#include "GraphicLib/Logger.h"

#include <memory>
#include <unordered_map>

namespace GraphicLib {
class IExternalLogSystem;
class InternalLogger final {
public:
    struct Message {
        Logger::Severity severity{};
        const char* source{};
        const char* type{};
        const char* text{};
    };
    static InternalLogger& Get();
    void SetCallback(Logger::MessageCallback callback, const void* userData);
    void SetSeverity(Logger::Severity severity);
    void LogMessage(const Message& message);
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
