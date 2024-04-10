#ifndef IMAGE_H

#define IMAGE_H

#include "error.h"

/// <summary>
/// load an opengl texture
/// </summary>
/// <param name="handle">opengl handle</param>
/// <param name="path">path to the image</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_IMAGE_LOAD on failure</returns>
err_t image_load(u32* handle, cstr path);

/// <summary>
/// load and overwrite an opengl texture
/// </summary>
/// <param name="handle">opengl handle</param>
/// <param name="path">path to the image</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL, or ERROR_IMAGE_LOAD on failure</returns>
err_t image_reload(u32* handle, cstr path);

/// <summary>
/// free the resources of an image
/// </summary>
/// <param name="handle">opengl handle</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t image_destroy(u32* handle);

#endif