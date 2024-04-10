#ifndef ENDIAN_H

#define ENDIAN_H

#include "typedef.h"

typedef enum endian_t {
	ENDIAN_LITTLE = 0,
	ENDIAN_BIGLY = 1
} endian_t;

/// <summary>
/// detects the endianness of the current system
/// </summary>
/// <returns>ENDIAN_LITTLE or ENDIAN_BIGLY</returns>
endian_t endianness_detect();

mem memcpy_inv(mem dest, cmem src, u64 len);

#endif
