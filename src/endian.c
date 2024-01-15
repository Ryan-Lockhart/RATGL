#include "endian.h"

#include "typedef.h"

endian_t endianness_detect()
{
    int i = 1;
    str p = (str)&i;

    return p[0] == 1 ? ENDIAN_LITTLE : ENDIAN_BIGLY;
}

mem memcpy_inv(mem dest, cmem src, u64 len)
{
    str d = (str)dest + len - 1;
    cstr s = src;
    while (len--)
        *d-- = *s++;
    return dest;
}
