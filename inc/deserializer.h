#ifndef DESERIALIZER_H

#define DESERIALIZER_H

#include "error.h"

struct vec2_t;
struct vec3_t;
struct vec4_t;

/// <summary>
/// Deserializes the size of a byte buffer.
/// </summary>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL on failure</returns>
err_t deserialize_size(u64* size, const byte* buffer);

/// <summary>
/// Deserializes the size and data of a float array.
/// </summary>
/// <param name="array">The array of floats. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t deserialize_floats(f32** array, u64* size, const byte* buffer);

/// <summary>
/// Deserializes the size and data of an unsigned 32-bit integer array.
/// </summary>
/// <param name="array">The array of unsigned 32-bit integers. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t deserialize_u32s(u32** array, u64* size, const byte* buffer);

/// <summary>
/// Deserializes the size and data of a vec2 array.
/// </summary>
/// <param name="array">The array of vec2s. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t deserialize_vec2s(struct vec2_t** array, u64* size, const byte* buffer);

/// <summary>
/// Deserializes the size and data of a vec3 array.
/// </summary>
/// <param name="array">The array of vec3s. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t deserialize_vec3s(struct vec3_t** array, u64* size, const byte* buffer);

/// <summary>
/// Deserializes the size and data of a vec4 array.
/// </summary>
/// <param name="array">The array of vec4s. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t deserialize_vec4s(struct vec4_t** array, u64* size, const byte* buffer);

#endif
