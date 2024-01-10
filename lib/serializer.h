#ifndef SERIALIZER_H

#define SERIALIZER_H

#include "typedef.h"

/// <summary>
/// Serializes the size and data of a float array.
/// </summary>
/// <param name="buffer">The serialzed binary data. It must be freed if successful.</param>
/// <param name="array">The array of floats.</param>
/// <param name="size">The size of the array.</param>
/// <returns>0 on success, -1 on failure</returns>
int serialize_floats(byte** buffer, const float* array, u64 size);

/// <summary>
/// Serializes the size and data of an unsigned 32-bit integer array.
/// </summary>
/// <param name="buffer">The serialzed binary data. It must be freed if successful.</param>
/// <param name="array">The array of unsigned 32-bit integers.</param>
/// <param name="size">The size of the array.</param>
/// <returns>0 on success, -1 on failure.</returns>
int serialize_u32s(byte** buffer, const u32* array, u64 size);

#endif
