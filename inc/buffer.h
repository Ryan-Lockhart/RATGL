#ifndef BUFFER_H

#define BUFFER_H

#include "error.h"

err_t index_buffer_create(u32* buffer, const u8* data, u64 count);
err_t index_buffer_create_ex(u32* buffer, const u8* data, u64 count, u32 mode);

err_t color_buffer_create(u32* buffer, const struct color_t* data, u64 count);
err_t color_buffer_create_ex(u32* buffer, const struct color_t* data, u64 count, u32 mode);

err_t element_buffer_create(u32* buffer, const u32* data, u64 count);
err_t element_buffer_create_ex(u32* buffer, const u32* data, u64 count, u32 mode);

err_t vec2_buffer_create(u32* buffer, const struct vec2_t* data, u64 count);
err_t vec2_buffer_create_ex(u32* buffer, const struct vec2_t* data, u64 count, u32 mode);

err_t vec3_buffer_create(u32* buffer, const struct vec3_t* data, u64 count);
err_t vec3_buffer_create_ex(u32* buffer, const struct vec3_t* data, u64 count, u32 mode);

err_t vec4_buffer_create(u32* buffer, const struct vec4_t* data, u64 count);
err_t vec4_buffer_create_ex(u32* buffer, const struct vec4_t* data, u64 count, u32 mode);

#endif