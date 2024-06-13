#include "GraphicLib/Model3d.h"

#include "GraphicLib/Utilities/Model3dUtils.h"
#include "InternalLogger.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <format>

namespace GraphicLib {
void Model3d::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }
    _id.IsInitialised = true;
}

void Model3d::Set(const std::array<char, MAX_MODEL_PATH_SIZE>& filePath, const std::span<const EModel3dImportSettings>& importSettings) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    if (filePath[0] == '\0') {
        LOG_INTERNAL_ERROR("filepath is empty");
        return;
    }

    if (importSettings.size() == 0) {
        LOG_INTERNAL_ERROR("importSettings is empty");
        return;
    }

    if (importSettings.size() > MAX_MODEL_IMPORT_SETTINGS_SIZE) {
        const std::string logText = std::format("importSetting size is greater then MAX_MODEL_IMPORT_SETTINGS_SIZE {}", MAX_MODEL_IMPORT_SETTINGS_SIZE);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    std::array<unsigned int, MAX_MODEL_IMPORT_SETTINGS_SIZE> assimpPostprocesses{};
    if (!Model3dUtils::ConvertModelImportSettings(importSettings, assimpPostprocesses)) {
        LOG_INTERNAL_ERROR("importSettings conversion failed");
        return;
    }

    // unsigned int postprocessFlags{};
    // for (size_t i{}; i < importSettings.size(); ++i) {
    //     postprocessFlags |= assimpPostprocesses.at(i);
    // }

    // Assimp::Importer assimpImporter;
    // assimpImporter.ReadFile(filePath.data(), postprocessFlags);
}
} // namespace GraphicLib