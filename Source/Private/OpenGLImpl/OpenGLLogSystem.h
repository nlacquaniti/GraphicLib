#pragma once

#include "IExternalLogSystem.h"

namespace GraphicLib::OpenGLImpl {
class OpenGLLogSystem final : public IExternalLogSystem {
private:
    void _onAttach() override;
    void _onDetach() override;
};
} // namespace GraphicLib::OpenGLImpl
