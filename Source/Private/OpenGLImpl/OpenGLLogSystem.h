#pragma once

#include "IExternalLogSystem.h"

namespace GraphicLib {
namespace OpenGLImpl {
class OpenGLLogSystem final : public IExternalLogSystem {
private:
    void _onAttach() override;
    void _onDetach() override;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
