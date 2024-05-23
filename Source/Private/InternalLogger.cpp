#include "InternalLogger.h"

#include "IExternalLogSystem.h"
#include <cassert>
#include <utility>

namespace GraphicLib {
InternalLogger* InternalLogger::_instance{};

InternalLogger& InternalLogger::Get() {
    if (_instance == nullptr) {
        _instance = new InternalLogger();
    }
    return *_instance;
}

void InternalLogger::SetCallback(Logger::MessageCallback callback, const void* userData) {
    assert(callback != nullptr);
    _callback = callback;
    _userData = userData;
}

void InternalLogger::SetSeverity(Logger::Severity severity) {
    _severity = severity;
}

void InternalLogger::LogMessage(const Message& message) {
    if (message.severity <= _severity) {
        Logger::Message debuggerMessage{
            message.category,
            _severity,
            message.source,
            message.text,
            _userData,
        };
        _callback(debuggerMessage);
    }
}

void InternalLogger::LogInternalNotification(const char* source, const char* text) {
    LogMessage(Message{Logger::Category::INTERNAL, Logger::Severity::NOTIFICATION, source, text});
}

void InternalLogger::LogInternalError(const char* source, const char* text) {
    LogMessage(Message{Logger::Category::INTERNAL, Logger::Severity::HIGH, source, text});
}

std::size_t InternalLogger::AttachExternalLogSystem(std::unique_ptr<IExternalLogSystem> externalLogSystem) {
    static std::size_t idCounter{};
    assert(idCounter < std::numeric_limits<std::size_t>::max());
    externalLogSystem->_setMessageLogCallback([](const Message& message) { InternalLogger::Get().LogMessage(message); });
    externalLogSystem->OnAttach();
    _externalLogSystems.emplace(std::make_pair(idCounter, std::move(externalLogSystem)));
    return idCounter++;
}

void InternalLogger::DetachExternalLogSystem(std::size_t id) {
    const auto elementPos = _externalLogSystems.find(id);
    assert(elementPos != _externalLogSystems.cend());
    elementPos->second->OnDetach();
    _externalLogSystems.erase(elementPos);
}
} // namespace GraphicLib
