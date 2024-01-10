#ifndef VERTEX_ARRAY_H

#define VERTEX_ARRAY_H

#include "typedef.h"

typedef struct vertex_array_t {
	u32 vao;
	u32 vbo;
	u32 ebo;
	u32 index;
} vertex_array_t;

int vertex_array_create(vertex_array_t* vao, u32 index, const float* vertices, u64 verticesSize, const u32* indices, u64 indicesSize);
int vertex_array_delete(vertex_array_t* vao);

int vertex_array_activate(const vertex_array_t* vao);
int vertex_array_deactive();

int vertex_buffer_create(u32* vbo, const float* vertices, u64 verticesSize);

int element_buffer_create(u32* ebo, const u32* indices, u64 indicesSize);

#endif