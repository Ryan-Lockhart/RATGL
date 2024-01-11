#include "serializer.h"

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SERIALIZE_TYPE u64

err_t serialize_size(byte** buffer, u64 arr_size, u64 elem_size)
{
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = buffer_create(buffer, arr_size * elem_size);

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    memcpy(&translator.element, &arr_size, sizeof(SERIALIZE_TYPE));
    memcpy(*buffer, translator.bytes, sizeof(SERIALIZE_TYPE));

    return ERROR_NONE;
}

err_t buffer_create(byte** buffer, u64 mem_size)
{
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    u64 buff_size = (sizeof(u64) + mem_size) * sizeof(byte);

    *buffer = (byte*)malloc(buff_size);

    if (*buffer == NULL) return error_alloc_fail("byte", buff_size, __FILE__, __LINE__);

    return ERROR_NONE;
}

err_t buffer_destroy(byte** buffer)
{
    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    free(*buffer);
    *buffer = NULL;

    return ERROR_NONE;
}

#undef SERIALIZE_TYPE
#define SERIALIZE_TYPE f32

err_t serialize_floats(byte** buffer, const f32* array, u64 size)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);

    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = serialize_size(buffer, size, sizeof(SERIALIZE_TYPE));

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    byte* array_base_ptr = *buffer + sizeof(u64);

    for (u64 i = 0; i < size; ++i)
    {
        memcpy(&translator.element, array + i, sizeof(SERIALIZE_TYPE));
        memcpy(array_base_ptr + i * sizeof(SERIALIZE_TYPE), translator.bytes, sizeof(SERIALIZE_TYPE));
    }

    return ERROR_NONE;
}

#undef SERIALIZE_TYPE
#define SERIALIZE_TYPE u32

err_t serialize_u32s(byte** buffer, const u32* array, u64 size)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);

    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = serialize_size(buffer, size, sizeof(SERIALIZE_TYPE));

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    byte* array_base_ptr = *buffer + sizeof(u64);

    for (u64 i = 0; i < size; ++i)
    {
        memcpy(&translator.element, array + i, sizeof(SERIALIZE_TYPE));
        memcpy(array_base_ptr + i * sizeof(SERIALIZE_TYPE), translator.bytes, sizeof(SERIALIZE_TYPE));
    }

    return ERROR_NONE;
}

#undef SERIALIZE_TYPE
#define SERIALIZE_TYPE vec2_t

err_t serialize_vec2s(byte** buffer, const vec2_t* array, u64 size)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);

    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = serialize_size(buffer, size, sizeof(SERIALIZE_TYPE));

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    byte* array_base_ptr = *buffer + sizeof(u64);

    for (u64 i = 0; i < size; ++i)
    {
        memcpy(&translator.element, array + i, sizeof(SERIALIZE_TYPE));
        memcpy(array_base_ptr + i * sizeof(SERIALIZE_TYPE), translator.bytes, sizeof(SERIALIZE_TYPE));
    }

    return ERROR_NONE;
}

#undef SERIALIZE_TYPE
#define SERIALIZE_TYPE vec3_t

err_t serialize_vec3s(byte** buffer, const vec3_t* array, u64 size)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);

    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = serialize_size(buffer, size, sizeof(SERIALIZE_TYPE));

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    byte* array_base_ptr = *buffer + sizeof(u64);

    for (u64 i = 0; i < size; ++i)
    {
        memcpy(&translator.element, array + i, sizeof(SERIALIZE_TYPE));
        memcpy(array_base_ptr + i * sizeof(SERIALIZE_TYPE), translator.bytes, sizeof(SERIALIZE_TYPE));
    }

    return ERROR_NONE;
}

#undef SERIALIZE_TYPE
#define SERIALIZE_TYPE vec4_t

err_t serialize_vec4s(byte** buffer, const vec4_t* array, u64 size)
{
    if (array == NULL) return error_param_null("array", __FILE__, __LINE__);

    if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
    if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

    err_t err = serialize_size(buffer, size, sizeof(SERIALIZE_TYPE));

    if (err > 0) return err;

    union { SERIALIZE_TYPE element; byte bytes[sizeof(SERIALIZE_TYPE)]; } translator;

    // offset pointer to the beginning of the array bytes portion of the buffer
    byte* array_base_ptr = *buffer + sizeof(u64);

    for (u64 i = 0; i < size; ++i)
    {
        memcpy(&translator.element, array + i, sizeof(SERIALIZE_TYPE));
        memcpy(array_base_ptr + i * sizeof(SERIALIZE_TYPE), translator.bytes, sizeof(SERIALIZE_TYPE));
    }

    return ERROR_NONE;
}
