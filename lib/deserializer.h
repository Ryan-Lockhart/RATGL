#ifndef DESERIALIZER_H

#define DESERIALIZER_H

#include "typedef.h"

/// <summary>
/// Serializes the size and data of a float array.
/// </summary>
/// <param name="array">The array of floats. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>0 on success, -1 on failure</returns>
int deserialize_floats(float** array, u64* size, const byte* buffer);

/// <summary>
/// Serializes the size and data of an unsigned 32-bit integer array.
/// </summary>
/// <param name="array">The array of unsigned 32-bit integers. It must be freed if successful.</param>
/// <param name="size">The size of the array.</param>
/// <param name="buffer">The serialzed binary data.</param>
/// <returns>0 on success, -1 on failure.</returns>
int deserialize_u32s(u32** array, u64* size, const byte* buffer);

#endif
