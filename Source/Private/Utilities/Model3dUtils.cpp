#include "GraphicLib/Utilities/Model3dUtils.h"

#include "GraphicLib/Model3d.h"
#include "InternalLogger.h"

#include <assimp/postprocess.h>
#include <urlmon.h>
#include <format>

namespace GraphicLib {
const char* Model3dUtils::ModelImportSettingToString(EModel3dImportSettings importSetting) {
    switch (importSetting) {
        case EModel3dImportSettings::NONE:
            return "NONE";
        case EModel3dImportSettings::CALC_TANGENT_SPACE:
            return "CALC_TANGENT_SPACE";
        case EModel3dImportSettings::JOIN_IDENTICAL_VERTICES:
            return "JOIN_IDENTICAL_VERTICES";
        case EModel3dImportSettings::MAKE_LEFT_HANDED:
            return "MAKE_LEFT_HANDED";
        case EModel3dImportSettings::TRIANGULATE:
            return "TRIANGULATE";
        case EModel3dImportSettings::REMOVE_COMPONENT:
            return "REMOVE_COMPONENT";
        case EModel3dImportSettings::GEN_NORMALS:
            return "GEN_NORMALS";
        case EModel3dImportSettings::GEN_SMOOTH_NORMALS:
            return "GEN_SMOOTH_NORMALS";
        case EModel3dImportSettings::SPLIT_LARGE_MESHES:
            return "SPLIT_LARGE_MESHES";
        case EModel3dImportSettings::PRE_TRANSFORM_VERTICES:
            return "PRE_TRANSFORM_VERTICES";
        case EModel3dImportSettings::LIMIT_BONE_WEIGHTS:
            return "LIMIT_BONE_WEIGHTS";
        case EModel3dImportSettings::VALIDATE_DATA_STRUCTURE:
            return "VALIDATE_DATA_STRUCTURE";
        case EModel3dImportSettings::IMPROVE_CACHE_LOCALITY:
            return "IMPROVE_CACHE_LOCALITY";
        case EModel3dImportSettings::REMOVE_REDUNDANT_MATERIALS:
            return "REMOVE_REDUNDANT_MATERIALS";
        case EModel3dImportSettings::FIX_INFACING_NORMALS:
            return "FIX_INFACING_NORMALS";
        case EModel3dImportSettings::SORT_BY_P_TYPE:
            return "SORT_BY_P_TYPE";
        case EModel3dImportSettings::FIND_DEGENERATES:
            return "FIND_DEGENERATES";
        case EModel3dImportSettings::FIND_INVALID_DATA:
            return "FIND_INVALID_DATA";
        case EModel3dImportSettings::GEN_UV_COORDS:
            return "GEN_UV_COORDS";
        case EModel3dImportSettings::TRANSFORM_UV_COORDS:
            return "TRANSFORM_UV_COORDS";
        case EModel3dImportSettings::FIND_INSTANCES:
            return "FIND_INSTANCES";
        case EModel3dImportSettings::OPTIMIZE_MESHES:
            return "OPTIMIZE_MESHES";
        case EModel3dImportSettings::OPTIMIZE_GRAPH:
            return "OPTIMIZE_GRAPH";
        case EModel3dImportSettings::FLIP_U_VS:
            return "FLIP_U_VS";
        case EModel3dImportSettings::FLIP_WINDING_ORDER:
            return "FLIP_WINDING_ORDER";
        case EModel3dImportSettings::SPLIT_BY_BONE_COUNT:
            return "SPLIT_BY_BONE_COUNT";
        case EModel3dImportSettings::DEBONE:
            return "DEBONE";
        case EModel3dImportSettings::GLOBAL_SCALE:
            return "GLOBAL_SCALE";
    }
    return "ERROR";
}

bool Model3dUtils::ConvertModelImportSetting(EModel3dImportSettings importSetting, unsigned int& outImportSetting) {
    switch (importSetting) {
        case EModel3dImportSettings::CALC_TANGENT_SPACE:
            outImportSetting = aiProcess_CalcTangentSpace;
            return true;
        case EModel3dImportSettings::JOIN_IDENTICAL_VERTICES:
            outImportSetting = aiProcess_JoinIdenticalVertices;
            return true;
        case EModel3dImportSettings::MAKE_LEFT_HANDED:
            outImportSetting = aiProcess_MakeLeftHanded;
            return true;
        case EModel3dImportSettings::TRIANGULATE:
            outImportSetting = aiProcess_Triangulate;
            return true;
        case EModel3dImportSettings::REMOVE_COMPONENT:
            outImportSetting = aiProcess_RemoveComponent;
            return true;
        case EModel3dImportSettings::GEN_NORMALS:
            outImportSetting = aiProcess_GenNormals;
            return true;
        case EModel3dImportSettings::GEN_SMOOTH_NORMALS:
            outImportSetting = aiProcess_GenSmoothNormals;
            return true;
        case EModel3dImportSettings::SPLIT_LARGE_MESHES:
            outImportSetting = aiProcess_SplitLargeMeshes;
            return true;
        case EModel3dImportSettings::PRE_TRANSFORM_VERTICES:
            outImportSetting = aiProcess_PreTransformVertices;
            return true;
        case EModel3dImportSettings::LIMIT_BONE_WEIGHTS:
            outImportSetting = aiProcess_LimitBoneWeights;
            return true;
        case EModel3dImportSettings::VALIDATE_DATA_STRUCTURE:
            outImportSetting = aiProcess_ValidateDataStructure;
            return true;
        case EModel3dImportSettings::IMPROVE_CACHE_LOCALITY:
            outImportSetting = aiProcess_ImproveCacheLocality;
            return true;
        case EModel3dImportSettings::REMOVE_REDUNDANT_MATERIALS:
            outImportSetting = aiProcess_RemoveRedundantMaterials;
            return true;
        case EModel3dImportSettings::FIX_INFACING_NORMALS:
            outImportSetting = aiProcess_FixInfacingNormals;
            return true;
        case EModel3dImportSettings::SORT_BY_P_TYPE:
            outImportSetting = aiProcess_SortByPType;
            return true;
        case EModel3dImportSettings::FIND_DEGENERATES:
            outImportSetting = aiProcess_FindDegenerates;
            return true;
        case EModel3dImportSettings::FIND_INVALID_DATA:
            outImportSetting = aiProcess_FindInvalidData;
            return true;
        case EModel3dImportSettings::GEN_UV_COORDS:
            outImportSetting = aiProcess_GenUVCoords;
            return true;
        case EModel3dImportSettings::TRANSFORM_UV_COORDS:
            outImportSetting = aiProcess_TransformUVCoords;
            return true;
        case EModel3dImportSettings::FIND_INSTANCES:
            outImportSetting = aiProcess_FindInstances;
            return true;
        case EModel3dImportSettings::OPTIMIZE_MESHES:
            outImportSetting = aiProcess_OptimizeMeshes;
            return true;
        case EModel3dImportSettings::OPTIMIZE_GRAPH:
            outImportSetting = aiProcess_OptimizeGraph;
            return true;
        case EModel3dImportSettings::FLIP_U_VS:
            outImportSetting = aiProcess_FlipUVs;
            return true;
        case EModel3dImportSettings::FLIP_WINDING_ORDER:
            outImportSetting = aiProcess_FlipWindingOrder;
            return true;
        case EModel3dImportSettings::SPLIT_BY_BONE_COUNT:
            outImportSetting = aiProcess_SplitByBoneCount;
            return true;
        case EModel3dImportSettings::DEBONE:
            outImportSetting = aiProcess_Debone;
            return true;
        case EModel3dImportSettings::GLOBAL_SCALE:
            outImportSetting = aiProcess_GlobalScale;
            return true;
        case GraphicLib::EModel3dImportSettings::NONE:
            break;
    }

    const std::string errorText = std::format("EModel3dImportSetting {}", Model3dUtils::ModelImportSettingToString(importSetting));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}

bool Model3dUtils::ConvertModelImportSettings(const std::span<const EModel3dImportSettings>& importSettings, const std::span<unsigned int>& outImportSettings) {
    if (importSettings.size() != outImportSettings.size()) {
        const std::string errorText =
            std::format("importSettings size {} and outImportSettings size {} don't match", importSettings.size(), outImportSettings.size());
        LOG_INTERNAL_ERROR(errorText.c_str());
        return false;
    }

    for (std::size_t i{}; i < importSettings.size(); ++i) {
        const EModel3dImportSettings& importSetting = importSettings[i];
        if (!Model3dUtils::ConvertModelImportSetting(importSetting, outImportSettings[i])) {
            const std::string errorText =
                std::format("Conversion EModel3dImportSetting::{} at index {} failed", Model3dUtils::ModelImportSettingToString(importSetting), i);
            return false;
        }
    }
    return true;
}
} // namespace GraphicLib