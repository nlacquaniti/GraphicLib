#pragma once

#include "IExternalLogSystem.h"

namespace GraphicLib {
namespace OpenGLImpl {
class GLFWLogSystem final : public IExternalLogSystem {
private:
    void _onAttach() override;
    void _onDetach() override;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
