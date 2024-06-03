#pragma once

#include "InternalLogger.h"

namespace GraphicLib {
class IExternalLogSystem {
public:
    using MessageLogCallback = void (*)(const InternalLogger::Message&);
    virtual ~IExternalLogSystem() = default;
    void OnAttach();
    void OnDetach();
    MessageLogCallback GetMessageLogCallback() const;

private:
    friend class InternalLogger;
    virtual void _onAttach() = 0;
    virtual void _onDetach() = 0;
    void _setMessageLogCallback(MessageLogCallback messageLogCallback);
    MessageLogCallback _messageLogCallback{};
};
} // namespace GraphicLib
