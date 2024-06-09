#pragma once

#include "GraphicLib/DLL_API.h"
#include <array>

namespace GraphicLib {
struct Model3dData {
    std::array<char, 256> Path;
};

class DLL_API Model3d {
    Model3d() noexcept = default;
    Model3d(Model3d&&) noexcept = default;
    Model3d& operator=(Model3d&&) noexcept = default;
    Model3d(const Model3d&) = delete;
    Model3d& operator=(const Model3d&) = delete;
    ~Model3d() noexcept = default;
    void Initialise()
};
} // namespace GraphicLib