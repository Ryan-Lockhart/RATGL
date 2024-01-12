#ifndef VERTEX_ARRAY_H

#define VERTEX_ARRAY_H

#include "error.h"

typedef struct vertex_array_t {
	u32 vao;
	u32 vbo;
	u32 ebo;
	u32 index;
} vertex_array_t;

struct vec3_t;

err_t vertex_array_create(vertex_array_t* vao, u32 index, const struct vec3_t* vertices, u64 verticesSize, const u32* indices, u64 indicesSize);
err_t vertex_array_create_f32s(vertex_array_t* vao, u32 index, const f32* vertices, u64 verticesSize, const u32* indices, u64 indicesSize);

err_t vertex_array_delete(vertex_array_t* vao);

err_t vertex_array_activate(const vertex_array_t* vao);
err_t vertex_array_deactive();

err_t vertex_buffer_create(u32* vbo, const struct vec3_t* vertices, u64 verticesSize);
err_t vertex_buffer_create_f32s(u32* vbo, const f32* vertices, u64 verticesSize);

err_t element_buffer_create(u32* ebo, const u32* indices, u64 indicesSize);

#endif