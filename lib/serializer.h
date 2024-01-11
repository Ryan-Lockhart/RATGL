#ifndef SERIALIZER_H

#define SERIALIZER_H

#include "error.h"

struct vec2_t;
struct vec3_t;
struct vec4_t;

/// <summary>
/// allocates the buffer and serializes the size
/// </summary>
/// <param name="buffer">- serialzed binary data</param>
/// <param name="arr_size">- size of the array</param>
/// <param name="elem_size">- size of an element</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_size(byte** buffer, u64 arr_size, u64 elem_size);

/// <summary>
/// allocates a buffer of bytes
/// </summary>
/// <param name="buffer">- serialized binary data</param>
/// <param name="mem_size">- size of the buffer in bytes</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t buffer_create(byte** buffer, u64 mem_size);

/// <summary>
/// deallocates a buffer of bytes
/// </summary>
/// <param name="buffer">- serialized binary data</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t buffer_destroy(byte** buffer);

/// <summary>
/// serializes the size and data of a float array
/// </summary>
/// <param name="buffer">- serialzed binary data. It must be freed if successful.</param>
/// <param name="array">- array of floats.</param>
/// <param name="size">- size of the array.</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_floats(byte** buffer, const f32* array, u64 size);

/// <summary>
/// serializes the size and data of an unsigned 32-bit integer array
/// </summary>
/// <param name="buffer">- serialzed binary data</param>
/// <param name="array">- array of unsigned 32-bit integers</param>
/// <param name="size">- size of the array</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_u32s(byte** buffer, const u32* array, u64 size);

/// <summary>
/// serializes the size and data of a vec2 array
/// </summary>
/// <param name="buffer">- serialized binary data</param>
/// <param name="array">- array of vec2s</param>
/// <param name="size">- size of the array</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_vec2s(byte** buffer, const struct vec2_t* array, u64 size);

/// <summary>
/// serializes the size and data of a vec3 array
/// </summary>
/// <param name="buffer">- serialized binary data</param>
/// <param name="array">- array of vec3s</param>
/// <param name="size">- size of the array</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_vec3s(byte** buffer, const struct vec3_t* array, u64 size);

/// <summary>
/// serializes the size and data of a vec4 array
/// </summary>
/// <param name="buffer">- serialized binary data</param>
/// <param name="array">- array of vec4s</param>
/// <param name="size">- size of the array</param>
/// <returns>ERROR_NONE on success, ERROR_PARAM_NULL, ERROR_PARAM_NONNULL, or ERROR_ALLOC_FAIL on failure</returns>
err_t serialize_vec4s(byte** buffer, const struct vec4_t* array, u64 size);

#endif
