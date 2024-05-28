#pragma once

#include "InternalLogger.h"

namespace GraphicLib {
class IExternalLogSystem {
public:
    IExternalLogSystem() = default;
    IExternalLogSystem(IExternalLogSystem&&) = default;
    IExternalLogSystem& operator=(IExternalLogSystem&&) = default;
    IExternalLogSystem(const IExternalLogSystem&) = delete;
    IExternalLogSystem& operator=(const IExternalLogSystem&) = delete;
    virtual ~IExternalLogSystem() = default;
    using MessageLogCallback = void (*)(const InternalLogger::Message&);
    void OnAttach();
    void OnDetach();
    [[nodiscard]] MessageLogCallback GetMessageLogCallback() const;

private:
    friend class InternalLogger;
    virtual void _onAttach() = 0;
    virtual void _onDetach() = 0;
    void _setMessageLogCallback(MessageLogCallback messageLogCallback);
    MessageLogCallback _messageLogCallback{};
};
} // namespace GraphicLib
