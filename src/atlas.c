#include "atlas.h"

#include <GL/glew.h>
#include <stb_image.h>

typedef struct atlas_t
{
	struct { i32 width, height; } image;
	struct { i32 width, height; } atlas;
	struct { i32 width, height; } glyph;
	i32 channels;
	u32 handle;
} atlas_t;

err_t atlas_load_grid(struct atlas_t* atlas, const byte* data, i32 atlas_width, i32 atlas_height, i32 image_width, i32 image_height);
err_t atlas_load_tower(struct atlas_t* atlas, const byte* data, i32 width, i32 height, i32 count);

err_t atlas_create(struct atlas_t** atlas)
{
	if (atlas == NULL) return error_param_null("atlas", __FILE__, __LINE__);
	if (*atlas != NULL) return error_param_notnull("*atlas", __FILE__, __LINE__);

	*atlas = malloc(sizeof(atlas_t));

	if (*atlas == NULL) return error_alloc_fail("atlas", sizeof(atlas_t), __FILE__, __LINE__);

	(*atlas)->image.width = 0;
	(*atlas)->image.height = 0;
	(*atlas)->atlas.width = 0;
	(*atlas)->atlas.height = 0;
	(*atlas)->glyph.width = 0;
	(*atlas)->glyph.height = 0;
	(*atlas)->channels = 0;
	(*atlas)->handle = 0;

	return ERROR_NONE;
}

err_t atlas_load(struct atlas_t* atlas, cstr path, i32 width, i32 height)
{
	if (atlas == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);

	stbi_set_flip_vertically_on_load(true);

	byte* data = stbi_load(path, &atlas->image.width, &atlas->image.height, &atlas->channels, 0);

	stbi_set_flip_vertically_on_load(false);

	if (data == NULL) return error_image_load(stbi_failure_reason(), __FILE__, __LINE__);

	if (atlas->image.width % width != 0)
	{
		stbi_image_free(data);
		return error_size_indivisible(atlas->image.width, width, __FILE__, __LINE__);
	}

	if (atlas->image.height % height != 0)
	{
		stbi_image_free(data);
		return error_size_indivisible(atlas->image.height, height, __FILE__, __LINE__);
	}

	err_t err = ERROR_NONE;

	glGenTextures(1, &atlas->handle);
	glBindTexture(GL_TEXTURE_2D_ARRAY, atlas->handle);

	if (image_width == width)
	{
		i32 count = image_height / height;

		err = atlas_load_tower(atlas->handle, data, width, count, count);
	}
	else err = atlas_load_grid(atlas->handle, data, width, height, image_width, image_height);

	stbi_image_free(data);

	return err;
}

err_t atlas_destroy(struct atlas_t* atlas)
{
	if (&atlas->handle == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (atlas->handle == 0) return error_param_notnull("*handle", __FILE__, __LINE__);

	glDeleteTextures(1, handle);

	return ERROR_NONE;
}

err_t atlas_load_grid(struct atlas_t* atlas, const byte* data, i32 atlas_width, i32 atlas_height, i32 image_width, i32 image_height)
{
	i32 glyph_width = image_width / atlas_width;
	i32 glyph_height = image_height / atlas_height;

	i32 count = atlas_width * atlas_height;

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, glyph_width, glyph_height, count, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	for (i32 i = 0; i < count; ++i)
	{
		div_t div_op = div(i, atlas_width);
		i32 x = div_op.rem * glyph_width, y = div_op.quot * glyph_height;

		for (i32 j = 0; j < glyph_height; ++j)
		{
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, j, i, glyph_width, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data[(x + (y + j * image_width)) * 4]);
		}
	}

	return ERROR_NONE;
}

err_t atlas_load_tower(struct atlas_t* atlas, const byte* data, i32 width, i32 height, i32 count)
{
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, count, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
