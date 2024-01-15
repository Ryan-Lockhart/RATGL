#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

err_t image_load(u32* handle, cstr path)
{
	if (handle == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	
	stbi_set_flip_vertically_on_load(true);

	i32 width, height, channels;
	byte* data = stbi_load(path, &width, &height, &channels, 0);

	stbi_set_flip_vertically_on_load(false);

	if (data == NULL) return error_image_load(stbi_failure_reason(), __FILE__, __LINE__);
	
	if (width % 2 != 0) return error_not_power_of_two("width", width, __FILE__, __LINE__);
	if (height % 2 != 0) return error_not_power_of_two("height", height, __FILE__, __LINE__);

	glGenTextures(1, handle);
	glBindTexture(GL_TEXTURE_2D, *handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return ERROR_NONE;
}

err_t atlas_load(u32* handle, cstr path, u64 width, u64 height)
{
	if (handle == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);

	stbi_set_flip_vertically_on_load(true);

	i32 image_width, image_height, channels;
	byte* data = stbi_load(path, &image_width, &image_height, &channels, 0);

	stbi_set_flip_vertically_on_load(false);

	if (data == NULL) return error_image_load(stbi_failure_reason(), __FILE__, __LINE__);

	if (width % 2 != 0) return error_not_power_of_two("image_width", image_width, __FILE__, __LINE__);
	if (height % 2 != 0) return error_not_power_of_two("image_height", image_height, __FILE__, __LINE__);

	glGenTextures(1, handle);
	glBindTexture(GL_TEXTURE_2D, *handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return ERROR_NONE;
}

err_t image_reload(u32* handle, cstr path)
{
	if (handle == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);

	if (*handle == 0) return error_param_notnull("*handle", __FILE__, __LINE__);

	stbi_set_flip_vertically_on_load(true);

	i32 width, height, channels;
	byte* data = stbi_load(path, &width, &height, &channels, 0);

	stbi_set_flip_vertically_on_load(false);

	if (data == NULL) return error_image_load(stbi_failure_reason(), __FILE__, __LINE__);

	if (width % 2 != 0) return error_not_power_of_two("width", width, __FILE__, __LINE__);
	if (height % 2 != 0) return error_not_power_of_two("height", height, __FILE__, __LINE__);

	glBindTexture(GL_TEXTURE_2D, *handle);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	return ERROR_NONE;
}

err_t image_destroy(u32* handle)
{
	if (handle == NULL) return error_param_null("handle", __FILE__, __LINE__);
	if (*handle == 0) return error_param_notnull("*handle", __FILE__, __LINE__);

	glDeleteTextures(1, handle);

	return ERROR_NONE;
}
