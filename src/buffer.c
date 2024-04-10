#include <GL/glew.h>

#include "error.h"

#include "color.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

int buffer_type_valid(u32 type);

#define BUFFER_TYPE_VALID 1
#define BUFFER_TYPE_INVALID 0

int buffer_draw_mode_valid(u32 mode);

#define DRAW_MODE_VALID 1
#define DRAW_MODE_INVALID 0

err_t index_buffer_create(u32* buffer, const u8* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(u8), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t index_buffer_create_ex(u32* buffer, const u8* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(u8), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t color_buffer_create(u32* buffer, const struct color_t* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(color_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t color_buffer_create_ex(u32* buffer, const struct color_t* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(color_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t element_buffer_create(u32* buffer, const u32* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t element_buffer_create_ex(u32* buffer, const u32* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec2_buffer_create(u32* buffer, const struct vec2_t* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec2_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec2_buffer_create_ex(u32* buffer, const struct vec2_t* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec2_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec3_buffer_create(u32* buffer, const struct vec3_t* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec3_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec3_buffer_create_ex(u32* buffer, const struct vec3_t* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec3_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec4_buffer_create(u32* buffer, const struct vec4_t* data, u64 count)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec4_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

err_t vec4_buffer_create_ex(u32* buffer, const struct vec4_t* data, u64 count, u32 mode)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (data == NULL) return error_param_null("data", __FILE__, __LINE__);

	if (buffer_draw_mode_valid(mode) != DRAW_MODE_VALID) return error_invalid_enum("mode", mode, __FILE__, __LINE__);

	glGenBuffers(1, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vec4_t), data, GL_STATIC_DRAW);

	return ERROR_NONE;
}

int buffer_type_valid(u32 type)
{
	switch (type)
	{
		case GL_ARRAY_BUFFER:
		case GL_ELEMENT_ARRAY_BUFFER:
		case GL_COPY_READ_BUFFER:
		case GL_COPY_WRITE_BUFFER:
		case GL_PIXEL_UNPACK_BUFFER:
		case GL_PIXEL_PACK_BUFFER:
		case GL_QUERY_BUFFER:
		case GL_TEXTURE_BUFFER:
		case GL_TRANSFORM_FEEDBACK_BUFFER:
		case GL_UNIFORM_BUFFER:
		case GL_DRAW_INDIRECT_BUFFER:
		case GL_ATOMIC_COUNTER_BUFFER:
		case GL_DISPATCH_INDIRECT_BUFFER:
		case GL_SHADER_STORAGE_BUFFER:
			return BUFFER_TYPE_VALID;
		default:
			return BUFFER_TYPE_INVALID;
	}
}

int buffer_draw_mode_valid(u32 mode)
{
	switch (mode)
	{
	case GL_STATIC_DRAW:
	case GL_DYNAMIC_DRAW:
	case GL_STREAM_DRAW:
		return DRAW_MODE_VALID;
	default:
		return DRAW_MODE_INVALID;
	}
}
