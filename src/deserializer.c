#include "deserializer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int deserialize_floats(float** array, u64* size, const byte* buffer)
{
    if (size == NULL)
    {
        printf("Address of size cannot be null!\n");

        return -1;
    }

    union {
        u64 u;
        byte bytes[sizeof(u64)];
    } u64_to_bytes;

    memcpy(&u64_to_bytes.bytes, buffer, sizeof(u64));
    *size = u64_to_bytes.u;

    *array = (float*)malloc((sizeof(float) * (*size)));

    if (*array == NULL)
    {
        printf("Failed to allocate memory for array!\n");

        return -1;
    }

    union {
        float f;
        byte bytes[sizeof(float)];
    } float_to_bytes;

    for (u64 i = 0; i < *size; ++i)
    {
        memcpy(&float_to_bytes.bytes, buffer + sizeof(u64) + (i * sizeof(float)), sizeof(float));
        memcpy(*array + i, &float_to_bytes.f, sizeof(float));
    }

    return 0;
}

int deserialize_u32s(u32** array, u64* size, const byte* buffer)
{
    if (size == NULL)
    {
        printf("Address of size cannot be null!\n");

        return -1;
    }

    union {
        u64 u;
        byte bytes[sizeof(u64)];
    } u64_to_bytes;

    memcpy(&u64_to_bytes.bytes, buffer, sizeof(u64));
    *size = u64_to_bytes.u;

    *array = (u32*)malloc((sizeof(u32) * (*size)));

    if (*array == NULL)
    {
        printf("Failed to allocate memory for array!\n");

        return -1;
    }

    union {
        u32 u;
        byte bytes[sizeof(u32)];
    } u32_to_bytes;

    for (u64 i = 0; i < *size; ++i)
    {
        memcpy(&u32_to_bytes.bytes, buffer + sizeof(u64) + (i * sizeof(u32)), sizeof(u32));
        memcpy(*array + i, &u32_to_bytes.u, sizeof(u32));
    }

    return 0;
}
