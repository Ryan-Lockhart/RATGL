#ifndef TYPEDEF_H

#define TYPEDEF_H

#include <float.h>

#define forever for (;;)

typedef unsigned char byte;

typedef unsigned char u8;

#define U8_MIN 0ui8
#define U8_MAX 255ui8

typedef signed char i8;

#define I8_MIN -127i8
#define I8_MAX 127i8

typedef unsigned short u16;

#define U16_MIN 0ui16
#define U16_MAX 65535ui16

typedef signed short i16;

#define I16_MIN -32767i16
#define I16_MAX 32767i16

typedef unsigned int u32;

#define U32_MIN 0ui32
#define U32_MAX 4294967295ui32

typedef signed int i32;

#define I32_MIN -2147483647i32
#define I32_MAX 2147483647i32

typedef unsigned long long u64;

#define U64_MIN 0ui64
#define U64_MAX 18446744073709551615ui64

typedef signed long long i64;

#define I64_MIN -9223372036854775807LLi64
#define I64_MAX 9223372036854775807LLi64

typedef float f32;

#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX

#define F32_EPSILON FLT_EPSILON

typedef double f64;

#define F64_MIN DBL_MIN
#define F64_MAX DBL_MAX

#define F64_EPSILON DBL_EPSILON

#ifdef WIN32

typedef unsigned int uptr;

#define UPTR_MIN U32_MIN
#define UPTR_MAX U32_MAX

typedef signed int iptr;

#define IPTR_MIN I32_MIN
#define IPTR_MAX I32_MAX

#else

typedef unsigned long long uptr;

#define UPTR_MIN U64_MIN
#define UPTR_MAX U64_MAX

typedef signed long long iptr;

#define IPTR_MIN I64_MIN
#define IPTR_MAX I64_MAX

#endif

typedef void* ptr;

typedef char* str;
typedef const char* cstr;

#define BUFFER_SIZE 512

#define LOG_SIZE 1024

#define BYTE_SIZE 8

#endif