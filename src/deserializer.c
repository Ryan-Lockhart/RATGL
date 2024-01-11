#include "deserializer.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DESERIALIZER_TYPE u64

err_t deserialize_size(u64* size, const byte* buffer)
{
    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    memcpy(&translator.bytes, buffer, sizeof(DESERIALIZER_TYPE));
    *size = translator.element;

    return ERROR_NONE;
}

#undef DESERIALIZER_TYPE
#define DESERIALIZER_TYPE f32

err_t deserialize_floats(f32** array, u64* size, const byte* buffer)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    deserialize_size(size, buffer);

    if (*array != NULL) return error_param_notnull("array", __FILE__, __LINE__);

    u64 mem_size = sizeof(DESERIALIZER_TYPE) * (*size);

    *array = (DESERIALIZER_TYPE*)malloc(mem_size);

    if (*array == NULL) return error_alloc_fail("f32", mem_size, __FILE__, __LINE__);

    // create union type to translate bytes to the appropriate type
    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    const byte* array_base_ptr = buffer + sizeof(u64);

    for (u64 i = 0; i < *size; ++i)
    {
        // copy the i-th element in bytes from the buffer into the bytes if the union
        memcpy(&translator.bytes, array_base_ptr + i * sizeof(DESERIALIZER_TYPE), sizeof(DESERIALIZER_TYPE));
        // copy the element of the union into the i-th element of the array
        memcpy(*array + i, &translator.element, sizeof(DESERIALIZER_TYPE));
    }

    return ERROR_NONE;
}

#undef DESERIALIZER_TYPE
#define DESERIALIZER_TYPE u32

err_t deserialize_u32s(u32** array, u64* size, const byte* buffer)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    deserialize_size(size, buffer);

    if (*array != NULL) return error_param_notnull("array", __FILE__, __LINE__);

    u64 mem_size = sizeof(DESERIALIZER_TYPE) * (*size);

    *array = (DESERIALIZER_TYPE*)malloc(mem_size);

    if (*array == NULL) return error_alloc_fail("u32", mem_size, __FILE__, __LINE__);

    // create union type to translate bytes to the appropriate type
    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    const byte* array_base_ptr = buffer + sizeof(u64);

    for (u64 i = 0; i < *size; ++i)
    {
        // copy the i-th element in bytes from the buffer into the bytes if the union
        memcpy(&translator.bytes, array_base_ptr + i * sizeof(DESERIALIZER_TYPE), sizeof(DESERIALIZER_TYPE));
        // copy the element of the union into the i-th element of the array
        memcpy(*array + i, &translator.element, sizeof(DESERIALIZER_TYPE));
    }

    return ERROR_NONE;
}

#undef DESERIALIZER_TYPE
#define DESERIALIZER_TYPE vec2_t

err_t deserialize_vec2s(vec2_t** array, u64* size, const byte* buffer)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    deserialize_size(size, buffer);

    if (*array != NULL) return error_param_notnull("array", __FILE__, __LINE__);

    u64 mem_size = sizeof(DESERIALIZER_TYPE) * (*size);

    *array = (DESERIALIZER_TYPE*)malloc(mem_size);

    if (*array == NULL) return error_alloc_fail("vec2_t", mem_size, __FILE__, __LINE__);

    // create union type to translate bytes to the appropriate type
    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    const byte* array_base_ptr = buffer + sizeof(u64);

    for (u64 i = 0; i < *size; ++i)
    {
        // copy the i-th element in bytes from the buffer into the bytes if the union
        memcpy(&translator.bytes, array_base_ptr + i * sizeof(DESERIALIZER_TYPE), sizeof(DESERIALIZER_TYPE));
        // copy the element of the union into the i-th element of the array
        memcpy(*array + i, &translator.element, sizeof(DESERIALIZER_TYPE));
    }

    return ERROR_NONE;
}

#undef DESERIALIZER_TYPE
#define DESERIALIZER_TYPE vec3_t

err_t deserialize_vec3s(vec3_t** array, u64* size, const byte* buffer)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    deserialize_size(size, buffer);

    if (*array != NULL) return error_param_notnull("array", __FILE__, __LINE__);

    u64 mem_size = sizeof(DESERIALIZER_TYPE) * (*size);

    *array = (DESERIALIZER_TYPE*)malloc(mem_size);

    if (*array == NULL) return error_alloc_fail("vec3_t", mem_size, __FILE__, __LINE__);

    // create union type to translate bytes to the appropriate type
    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    const byte* array_base_ptr = buffer + sizeof(u64);

    for (u64 i = 0; i < *size; ++i)
    {
        // copy the i-th element in bytes from the buffer into the bytes if the union
        memcpy(&translator.bytes, array_base_ptr + i * sizeof(DESERIALIZER_TYPE), sizeof(DESERIALIZER_TYPE));
        // copy the element of the union into the i-th element of the array
        memcpy(*array + i, &translator.element, sizeof(DESERIALIZER_TYPE));
    }

    return ERROR_NONE;
}

#undef DESERIALIZER_TYPE
#define DESERIALIZER_TYPE vec4_t

err_t deserialize_vec4s(vec4_t** array, u64* size, const byte* buffer)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

    if (size == NULL) return error_param_null("size", __FILE__, __LINE__);

    deserialize_size(size, buffer);

    if (*array != NULL) return error_param_notnull("array", __FILE__, __LINE__);

    u64 mem_size = sizeof(DESERIALIZER_TYPE) * (*size);

    *array = (DESERIALIZER_TYPE*)malloc(mem_size);

    if (*array == NULL) return error_alloc_fail("vec4_t", mem_size, __FILE__, __LINE__);

    // create union type to translate bytes to the appropriate type
    union { DESERIALIZER_TYPE element; byte bytes[sizeof(DESERIALIZER_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    const byte* array_base_ptr = buffer + sizeof(u64);

    for (u64 i = 0; i < *size; ++i)
    {
        // copy the i-th element in bytes from the buffer into the bytes if the union
        memcpy(&translator.bytes, array_base_ptr + i * sizeof(DESERIALIZER_TYPE), sizeof(DESERIALIZER_TYPE));
        // copy the element of the union into the i-th element of the array
        memcpy(*array + i, &translator.element, sizeof(DESERIALIZER_TYPE));
    }

    return ERROR_NONE;
}
