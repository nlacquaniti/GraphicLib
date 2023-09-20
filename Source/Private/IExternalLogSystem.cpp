#include "IExternalLogSystem.h"

namespace GraphicLib {
void IExternalLogSystem::OnAttach() {
    _onAttach();
}

void IExternalLogSystem::OnDetach() {
    _onDetach();
}

IExternalLogSystem::MessageLogCallback IExternalLogSystem::GetMessageLogCallback() const {
    return _messageLogCallback;
}

void IExternalLogSystem::_setMessageLogCallback(MessageLogCallback messageLogCallback) {
    _messageLogCallback = messageLogCallback;
}
} // namespace GraphicLib
