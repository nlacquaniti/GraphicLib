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
    // Check if the message can be logged.
    if (message.severity <= _severity) {
        Logger::Message debuggerMessage{
            _severity,
            message.source,
            message.type,
            message.text,
            _userData,
        };
        _callback(debuggerMessage);
    }
}

std::size_t InternalLogger::AttachExternalLogSystem(std::unique_ptr<IExternalLogSystem> externalLogSystem) {
    static std::size_t idCounter{};
    assert(idCounter < std::numeric_limits<std::size_t>::max());
    externalLogSystem->_setMessageLogCallback([](const Message& message) { InternalLogger::Get().LogMessage(message); });
    _externalLogSystems.emplace(std::make_pair(idCounter, std::move(externalLogSystem)));
    return idCounter++;
}

void InternalLogger::DetachExternalLogSystem(std::size_t id) {
    const auto elementPos = _externalLogSystems.find(id);
    assert(elementPos != _externalLogSystems.cend());
    _externalLogSystems.erase(elementPos);
}
} // namespace GraphicLib
