#include "GraphicLib/Model3d.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/Utilities/Model3dUtils.h"
#include "GraphicLib/VertexBuffer.h"
#include "InternalLogger.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <format>

namespace GraphicLib {
namespace {
Mesh _processMesh(aiMesh* assimpMesh, const aiScene*) {
    Mesh outputMesh;
    outputMesh.Initialise();

    std::vector<float> vertices;
    vertices.reserve(assimpMesh->mNumVertices);

    for (unsigned int i{}; i < assimpMesh->mNumVertices; ++i) {
        vertices.emplace_back(assimpMesh->mVertices[i].x);
        vertices.emplace_back(assimpMesh->mVertices[i].y);
        vertices.emplace_back(assimpMesh->mVertices[i].z);

        if (assimpMesh->HasTextureCoords(0)) {
            vertices.emplace_back(assimpMesh->mTextureCoords[i]->x);
            vertices.emplace_back(assimpMesh->mTextureCoords[i]->y);
        }
    }

    std::size_t vertexAttributesCount{};
    std::array<VertexAttribute, VertexBuffer::MAX_VERTEX_ATTRIBUTES_SIZE> vertexAttributes;

    // aPos must always be present.
    vertexAttributes.at(vertexAttributesCount).Name = {"aPos"};
    vertexAttributes.at(vertexAttributesCount).Count = 3;
    ++vertexAttributesCount;

    if (assimpMesh->HasTextureCoords(0)) {
        vertexAttributes.at(vertexAttributesCount).Name = {"aTexCoord"};
        vertexAttributes.at(vertexAttributesCount).Count = 2;
        ++vertexAttributesCount;
    }

    if (assimpMesh->HasFaces()) {
        std::vector<unsigned int> indices;
        indices.reserve(assimpMesh->mNumFaces * assimpMesh->mFaces[0].mNumIndices);
        for (unsigned int i{}; i < assimpMesh->mNumFaces; i++) {
            const aiFace& face = assimpMesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.emplace_back(face.mIndices[j]);
        }
    }

    outputMesh.SetVertexBuffer(std::move(vertices), vertexAttributes);
    return outputMesh;
}

void _processNode(aiNode* assimpNode, const aiScene* assimpScene, std::vector<Mesh>& meshes) {
    for (unsigned int i{}; i < assimpNode->mNumMeshes; ++i) {
        aiMesh* mesh = assimpScene->mMeshes[assimpNode->mMeshes[i]];
        meshes.push_back(_processMesh(mesh, assimpScene));
    }

    for (unsigned int i{}; i < assimpNode->mNumChildren; ++i) {
        _processNode(assimpNode->mChildren[i], assimpScene, meshes);
    }
}
} // namespace

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

    unsigned int postprocessFlags{};
    for (size_t i{}; i < importSettings.size(); ++i) {
        postprocessFlags |= assimpPostprocesses.at(i);
    }

    Assimp::Importer assimpImporter;
    const aiScene* assimpScene = assimpImporter.ReadFile(filePath.data(), postprocessFlags);
    if (assimpScene == nullptr || (assimpScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0U || assimpScene->mRootNode == nullptr) {
        const std::string logText = std::format("assimp error: {}", assimpImporter.GetErrorString());
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }
    _processNode(assimpScene->mRootNode, assimpScene, _meshes);
}
} // namespace GraphicLib