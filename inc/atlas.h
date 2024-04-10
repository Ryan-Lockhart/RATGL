#ifndef ATLAS_H

#define ATLAS_H

#include "error.h"

// opaque type for a two-dimensional texture atlas
typedef struct atlas_t;

/// <summary>
/// load an opengl texture atlas
/// </summary>
/// <param name="atlas">pointer to the atlas</param>
/// <param name="path">path to the image</param>
/// <param name="width">width of the atlas in glyphs</param>
/// <param name="height">height of the atlas in glyphs</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_IMAGE_LOAD, ERROR_NON_POWER_OF_TWO, or ERROR_SIZE_MISMATCH on failure</returns>
err_t atlas_load(struct atlas_t* atlas, cstr path, i32 width, i32 height);

/// <summary>
/// load and overwrite an opengl texture atlas
/// </summary>
/// <param name="atlas">pointer to the atlas</param>
/// <param name="path">path to the image</param>
/// <param name="width">width of the atlas in glyphs</param>
/// <param name="height">height of the atlas in glyphs</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL, ERROR_IMAGE_LOAD, ERROR_NON_POWER_OF_TWO, or ERROR_SIZE_MISMATCH on failure</returns>
err_t atlas_reload(struct atlas_t* atlas, cstr path, i32 width, i32 height);

/// <summary>
/// free the resources of an atlas
/// </summary>
/// <param name="atlas">pointer to the atlas</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t atlas_destroy(struct atlas_t* atlas);

#endif