#include "serializer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int serialize_floats(byte** buffer, const float* array, u64 size)
{
    if (buffer == NULL)
    {
        printf("Address to buffer is uninitialized!\n");

        return -1;
    }

    *buffer = (byte*)malloc((sizeof(u64) + (sizeof(float) * size)) * sizeof(byte));

    if (*buffer == NULL)
    {
        printf("Failed to allocate memory for serialization buffer!\n");

        return -1;
    }

    union {
        u64 u;
        byte bytes[sizeof(u64)];
    } u64_to_bytes;

    memcpy(&u64_to_bytes.u, &size, sizeof(u64));
    memcpy(*buffer, u64_to_bytes.bytes, sizeof(u64));

    union {
        float f;
        byte bytes[sizeof(float)];
    } float_to_bytes;

    for (u64 i = 0; i < size; ++i)
    {
        float_to_bytes.f = array[i];
        memcpy((*buffer) + sizeof(u64) + (i * sizeof(float)), &float_to_bytes.bytes, sizeof(float));
    }

    return 0;
}

int serialize_u32s(byte** buffer, const u32* array, u64 size)
{
    if (buffer == NULL)
    {
        printf("Address to buffer is uninitialized!\n");

        return -1;
    }

    *buffer = (byte*)malloc(sizeof(u64) + (sizeof(u32) * size));

    if (*buffer == NULL)
    {
        printf("Failed to allocate memory for serialization buffer!\n");

        return -1;
    }

    union {
        u64 u;
        byte bytes[sizeof(u64)];
    } u64_to_bytes;

    memcpy(&u64_to_bytes.u, &size, sizeof(u64));
    memcpy(*buffer, u64_to_bytes.bytes, sizeof(u64));

    union {
        u32 u;
        byte bytes[sizeof(u32)];
    } u32_to_bytes;

    for (u64 i = 0; i < size; ++i)
    {
        u32_to_bytes.u = array[i];
        memcpy((*buffer) + sizeof(u64) + (i * sizeof(u32)), u32_to_bytes.bytes, sizeof(u32));
    }

    return 0;
}
