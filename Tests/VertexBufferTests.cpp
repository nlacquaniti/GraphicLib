#include "VertexBufferTests.h"

#include <GraphicLib/GL_VertexBuffer.h>

#include <cassert>
#include <cstdio>
#include <cstring>

static void CreateTestVertexBuffer(GL_VertexBufferId* vertexBufferId,
    float* vertexData,
    size_t vertexDataSize,
    GL_VertexAttribute vertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE],
    size_t vertexAttributesCount) {
    GL_CreateVertexBuffer(vertexBufferId, vertexData, vertexDataSize, vertexAttributes,
        vertexAttributesCount);

    const GL_VertexBufferData* vertexBufferData =
        GL_Internal_FindVertexBufferData(*vertexBufferId);
    assert(vertexBufferData != nullptr);

    assert(vertexBufferData->VertexDataSize == vertexDataSize);
    for (size_t i = 0; i < vertexBufferData->VertexDataSize; ++i) {
        assert(vertexBufferData->VertexData[i] == vertexData[i]);
    }

    assert(vertexBufferData->VertexAttributesCount == vertexAttributesCount);
    for (size_t i = 0; i < vertexBufferData->VertexAttributesCount; ++i) {
        assert(strcmp(vertexBufferData->VertexAttributes[i].Name,
                   vertexAttributes[i].Name) == 0);
        assert(vertexBufferData->VertexAttributes[i].Count == vertexAttributes[i].Count);
    }
}

void TestCreateAndDeleteVertexBuffer() {
    const size_t vertexDataSize = 102;

    float* vertexData = GL_AllocateVertexData(vertexDataSize);
    assert(vertexData != nullptr);
    for (size_t i = 0; i < vertexDataSize; ++i) {
        vertexData[i] = 666.0f;
    }

    const size_t vertexAttributesSize = 1;
    GL_VertexAttribute vertexAttributes[] = {
        GL_VertexAttribute{.Name = "aPos", .Count = 3},
    };

    GL_VertexBufferId vertexBufferId;
    CreateTestVertexBuffer(&vertexBufferId, vertexData, vertexDataSize, vertexAttributes,
        vertexAttributesSize);
    assert(vertexBufferId == 0);

    GL_Internal_VertexBufferDataArray* vertexBufferDataArray =
        GL_Internal_GetVertexBufferDataArray();
    assert(vertexBufferDataArray->Count == 1);

    GL_DeleteVertexBuffer(vertexBufferId);
    assert(vertexBufferId == GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE);
    printf("TestCreateAndDeleteVertexBuffer COMPLETED\n");
}

void TestCreateAndDeleteAllVertexBuffer() {
    GL_Internal_VertexBufferDataArray* vertexBufferDataArray =
        GL_Internal_GetVertexBufferDataArray();

    const size_t vertexDataSize = 102;
    float* vertexData = GL_AllocateVertexData(vertexDataSize);
    assert(vertexData != nullptr);
    for (size_t i = 0; i < vertexDataSize; ++i) {
        vertexData[i] = 666.0f;
    }

    const size_t vertexAttributesSize = 1;
    GL_VertexAttribute vertexAttributes[] = {
        GL_VertexAttribute{.Name = "aPos", .Count = 3},
    };

    const size_t vertexBufferIdsSize = 10;
    GL_VertexBufferId vertexBufferIds[vertexBufferIdsSize];

    // Create
    for (size_t i = 0; i < vertexBufferIdsSize; ++i) {
        CreateTestVertexBuffer(&vertexBufferIds[i], vertexData, vertexDataSize,
            vertexAttributes, vertexAttributesSize);
        assert(vertexBufferIds[i] == i);
        assert(vertexBufferDataArray->Data[i].Id == &vertexBufferIds[i]);
    }
    assert(vertexBufferDataArray->Count == vertexBufferIdsSize);

    // Delete
    for (size_t i = 0; i < vertexBufferIdsSize; ++i) {
        GL_DeleteVertexBuffer(vertexBufferIds[i]);
        assert(vertexBufferIds[i] == GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE);
        // Check if the deleted element Id has been resetted.
        assert(vertexBufferDataArray->Data[vertexBufferDataArray->Count].Id == nullptr);
    }

    assert(vertexBufferDataArray->Count == 0);

    printf("TestCreateAndDeleteAllVertexBuffer COMPLETED\n");
}

void TestCreateAndDeleteVertexBufferFromTheMiddle() {
    GL_Internal_VertexBufferDataArray* vertexBufferDataArray =
        GL_Internal_GetVertexBufferDataArray();

    const size_t vertexDataSize = 102;
    float* vertexData = GL_AllocateVertexData(vertexDataSize);
    assert(vertexData != nullptr);
    for (size_t i = 0; i < vertexDataSize; ++i) {
        vertexData[i] = 666.0f;
    }

    const size_t vertexAttributesSize = 1;
    GL_VertexAttribute vertexAttributes[] = {
        GL_VertexAttribute{.Name = "aPos", .Count = 3},
    };

    const size_t vertexBufferIdsSize = 10;
    GL_VertexBufferId vertexBufferIds[vertexBufferIdsSize];

    // Create
    for (size_t i = 0; i < vertexBufferIdsSize; ++i) {
        CreateTestVertexBuffer(&vertexBufferIds[i], vertexData, vertexDataSize,
            vertexAttributes, vertexAttributesSize);
        assert(vertexBufferIds[i] == i);
        assert(vertexBufferDataArray->Data[i].Id == &vertexBufferIds[i]);
    }

    assert(vertexBufferDataArray->Count == vertexBufferIdsSize);

    // Delete
    const size_t firstVertexBufferIdToDelete = 5;
    const size_t vertexBufferIdsToDeleteCount = 3;
    for (size_t i = 0; i < vertexBufferIdsToDeleteCount; ++i) {
        const size_t indexToDelete = firstVertexBufferIdToDelete + i;
        GL_DeleteVertexBuffer(vertexBufferIds[indexToDelete]);
        assert(
            vertexBufferIds[indexToDelete] == GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE);

        // Check if the deleted element Id has been resetted.
        assert(vertexBufferDataArray->Data[vertexBufferDataArray->Count].Id == nullptr);
    }
    assert(vertexBufferDataArray->Count ==
           vertexBufferIdsSize - vertexBufferIdsToDeleteCount);

    // Mid delete check.
    for (size_t i = 0; i < vertexBufferIdsSize; ++i) {
        if (i < firstVertexBufferIdToDelete ||
            i >= firstVertexBufferIdToDelete + vertexBufferIdsToDeleteCount) {
            assert(*vertexBufferDataArray->Data[vertexBufferIds[i]].Id ==
                   vertexBufferIds[i]);
            assert(vertexBufferDataArray->Data[vertexBufferIds[i]].Id ==
                   &vertexBufferIds[i]);
        }
    }

    // Cleanup.
    for (size_t i = 0; i < vertexBufferDataArray->Count; ++i) {
        vertexBufferDataArray->Data[i].Id = nullptr;
    }
    vertexBufferDataArray->Count = 0;
    printf("TestCreateAndDeleteMultipleVertexBuffer COMPLETED\n");
}
