#include "GraphicLib/GL_VertexBuffer.h"

#include "OpenGLImpl/VertexBufferImpl.h"

#include <cassert>
#include <cstdlib>

// PUBLIC

float* GL_AllocateVertexData(size_t size) {
    return (float*)malloc(size * sizeof(float));
}

void GL_CreateVertexBuffer(GL_VertexBufferId* vertexBufferId,
    float* vertexData,
    size_t vertexDataSize,
    GL_VertexAttribute vertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE],
    size_t vertexAttributeCount) {
    int openGLVertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE];
    for (size_t i = 0; i < vertexAttributeCount; ++i) {
        openGLVertexAttributes[i] = vertexAttributes[i].Count;
    }

    GL_Internal_Id internalId;
    GL_Internal_InitialiseVertexBuffer(&internalId);
    GL_Internal_BindVertexBuffer(internalId);

    GL_Internal_SetVertexBuffer(
        vertexData, vertexDataSize, openGLVertexAttributes, vertexAttributeCount);

    GL_Internal_CreateVertexBufferData(vertexBufferId, vertexData, vertexDataSize,
        vertexAttributes, vertexAttributeCount, internalId);
}

void GL_BindVertexBuffer(GL_VertexBufferId id) {
    const GL_VertexBufferData* vertexBufferData = GL_Internal_FindVertexBufferData(id);
    GL_Internal_BindVertexBuffer(vertexBufferData->InternalId);
}

void GL_UnbindVertexBuffer() {
    GL_Internal_UnbindVertexBuffer();
}

void GL_DeleteVertexBuffer(GL_VertexBufferId id) {
    GL_VertexBufferData* vertexBufferData = GL_Internal_FindVertexBufferData(id);
    GL_Internal_DeleteVertexBuffer(&vertexBufferData->InternalId);
    GL_Internal_DeleteVertexBufferData(id);
}

const GL_VertexBufferData* GL_GetVertexBufferData(GL_VertexBufferId id) {
    return GL_Internal_FindVertexBufferData(id);
}

// INTERNAL

static GL_Internal_VertexBufferDataArray _vertexBufferDataArray;

GL_Internal_VertexBufferDataArray* GL_Internal_GetVertexBufferDataArray() {
    return &_vertexBufferDataArray;
}

void GL_Internal_CreateVertexBufferData(GL_VertexBufferId* vertexBufferId,
    float* vertexData,
    size_t vertexDataSize,
    GL_VertexAttribute vertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE],
    size_t vertexAttributeCount,
    unsigned int internalId) {
    if (_vertexBufferDataArray.Count == GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE) {
        assert(false);
        return;
    }

    *vertexBufferId = _vertexBufferDataArray.Count;

    GL_VertexBufferData* vertexBufferData =
        &_vertexBufferDataArray.Data[_vertexBufferDataArray.Count++];

    vertexBufferData->VertexData = vertexData;
    vertexBufferData->VertexDataSize = vertexDataSize;
    for (size_t i = 0; i < vertexAttributeCount; ++i) {
        vertexBufferData->VertexAttributes[i] = vertexAttributes[i];
    }
    vertexBufferData->VertexAttributesCount = vertexAttributeCount;
    vertexBufferData->Id = vertexBufferId;
    vertexBufferData->InternalId = internalId;
}

GL_VertexBufferData* GL_Internal_FindVertexBufferData(GL_VertexBufferId id) {
    if (id >= _vertexBufferDataArray.Count) {
        assert(false);
        return nullptr;
    }

    return &_vertexBufferDataArray.Data[id];
}

void GL_Internal_DeleteVertexBufferData(GL_VertexBufferId id) {
    if (id >= _vertexBufferDataArray.Count) {
        assert(false);
        return;
    }

    for (size_t i = id; i < _vertexBufferDataArray.Count - 1; ++i) {
        GL_VertexBufferId* tempCurrentId = _vertexBufferDataArray.Data[i].Id;
        _vertexBufferDataArray.Data[i] = _vertexBufferDataArray.Data[i + 1];
        _vertexBufferDataArray.Data[i + 1].Id = tempCurrentId;
        *_vertexBufferDataArray.Data[i].Id = i;
    }

    *_vertexBufferDataArray.Data[_vertexBufferDataArray.Count - 1].Id =
        GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE;
    _vertexBufferDataArray.Data[_vertexBufferDataArray.Count - 1].Id = nullptr;
    --_vertexBufferDataArray.Count;
}