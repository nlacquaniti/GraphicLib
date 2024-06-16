#pragma once

// PUBLIC

#define GL_ATTRIBUTE_NAME_SIZE 24ULL
#define GL_VERTEX_ATTRIBUTES_SIZE 16ULL

typedef size_t GL_VertexBufferId;

typedef struct {
    char Name[GL_ATTRIBUTE_NAME_SIZE];
    int Count;
} GL_VertexAttribute;

typedef struct {
    GL_VertexAttribute VertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE];
    const float* VertexData;
    GL_VertexBufferId* Id;
    size_t VertexDataSize;
    size_t VertexAttributesCount;
    unsigned int InternalId;
} GL_VertexBufferData;

float* GL_AllocateVertexData(size_t size);

void GL_CreateVertexBuffer(GL_VertexBufferId* vertexBufferId,
    float* vertexData,
    size_t vertexDataSize,
    GL_VertexAttribute vertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE],
    size_t vertexAttributeCount);

void GL_BindVertexBuffer(GL_VertexBufferId id);

void GL_UnbindVertexBuffer();

void GL_DeleteVertexBuffer(GL_VertexBufferId id);

const GL_VertexBufferData* GL_GetVertexBufferData(GL_VertexBufferId id);

// INTERNAL

#define GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE 1024ULL

typedef struct {
    GL_VertexBufferData Data[GL_INTERNAL_VERTEX_BUFFER_DATA_ARRAY_SIZE];
    size_t Count;
} GL_Internal_VertexBufferDataArray;

GL_Internal_VertexBufferDataArray* GL_Internal_GetVertexBufferDataArray();

void GL_Internal_CreateVertexBufferData(GL_VertexBufferId* vertexBufferId,
    float* vertexData,
    size_t vertexDataSize,
    GL_VertexAttribute vertexAttributes[GL_VERTEX_ATTRIBUTES_SIZE],
    size_t vertexAttributeCount,
    unsigned int internalId);

GL_VertexBufferData* GL_Internal_FindVertexBufferData(GL_VertexBufferId id);

void GL_Internal_DeleteVertexBufferData(GL_VertexBufferId id);
