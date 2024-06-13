#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Mesh.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"
#include <array>

namespace GraphicLib {
enum class EModel3dImportSettings : unsigned char {
    NONE,
    CALC_TANGENT_SPACE,
    JOIN_IDENTICAL_VERTICES,
    MAKE_LEFT_HANDED,
    TRIANGULATE,
    REMOVE_COMPONENT,
    GEN_NORMALS,
    GEN_SMOOTH_NORMALS,
    SPLIT_LARGE_MESHES,
    PRE_TRANSFORM_VERTICES,
    LIMIT_BONE_WEIGHTS,
    VALIDATE_DATA_STRUCTURE,
    IMPROVE_CACHE_LOCALITY,
    REMOVE_REDUNDANT_MATERIALS,
    FIX_INFACING_NORMALS,
    SORT_BY_P_TYPE,
    FIND_DEGENERATES,
    FIND_INVALID_DATA,
    GEN_UV_COORDS,
    TRANSFORM_UV_COORDS,
    FIND_INSTANCES,
    OPTIMIZE_MESHES,
    OPTIMIZE_GRAPH,
    FLIP_U_VS,
    FLIP_WINDING_ORDER,
    SPLIT_BY_BONE_COUNT,
    DEBONE,
    GLOBAL_SCALE,
};

class DLL_API Model3d {
public:
    static constexpr std::size_t MAX_MODEL_PATH_SIZE = 265;
    static constexpr std::size_t MAX_MODEL_IMPORT_SETTINGS_SIZE = static_cast<size_t>(EModel3dImportSettings::GLOBAL_SCALE);
    Model3d() noexcept = default;
    Model3d(Model3d&&) noexcept = default;
    Model3d& operator=(Model3d&&) noexcept = default;
    Model3d(const Model3d&) = delete;
    Model3d& operator=(const Model3d&) = delete;
    ~Model3d() noexcept = default;
    void Initialise();
    void Set(const std::array<char, MAX_MODEL_PATH_SIZE>& filePath, const std::span<const EModel3dImportSettings>& importSettings);
    void Draw(Shader& shader);
    [[nodiscard]] const char* GetModelPath() const;
    [[nodiscard]] std::span<const EModel3dImportSettings> GetImportSettings() const;
    [[nodiscard]] const std::vector<Mesh> GetMeshes() const;

private:
    std::array<char, MAX_MODEL_PATH_SIZE> _modelPath{};
    std::array<EModel3dImportSettings, MAX_MODEL_IMPORT_SETTINGS_SIZE> _modelImportSettings{};
    std::vector<Mesh> _meshes;
    UniqueIdentifier _id;
};
} // namespace GraphicLib