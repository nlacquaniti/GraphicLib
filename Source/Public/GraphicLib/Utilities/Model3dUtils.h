#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Model3d.h"

namespace GraphicLib {
class Model3dUtils {
public:
    DLL_API static const char* ModelImportSettingToString(EModel3dImportSettings importSetting);
    static bool ConvertModelImportSetting(EModel3dImportSettings importSetting, unsigned int& outImportSetting);
    static bool ConvertModelImportSettings(const std::span<const EModel3dImportSettings>& importSettings, const std::span<unsigned int>& outImportSettings);
};
} // namespace GraphicLib