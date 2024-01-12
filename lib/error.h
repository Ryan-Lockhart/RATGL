#ifndef ERROR_H

#define ERROR_H

#include "typedef.h"

typedef enum err_t {
	ERROR_NONE = 0,
	ERROR_ALLOC_FAIL = -1 << 0,
	ERROR_PARAM_NULL = -1 << 1,
	ERROR_PARAM_NOTNULL = -1 << 2,
	ERROR_COLOR_UNNORM = -1 << 3,
	ERROR_UNOPENABLE_FILE = -1 << 4,
	ERROR_UNCLOSEABLE_FILE = -1 << 5,
	ERROR_SIZE_MISMATCH = -1 << 6,
} err_t;

/// <summary>
/// logs and returns an error when a *alloc call fails to allocate memory
/// </summary>
/// <param name="type">type of the memory</param>
/// <param name="size">size of the memory</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_ALLOC_FAIL</returns>
err_t error_alloc_fail(cstr type, u64 size, cstr file, i32 line);

/// <summary>
/// logs and returns an error for when a non-null required parameter is null
/// </summary>
/// <param name="name">name of the null parameter</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_PARAM_NULL</returns>
err_t error_param_null(cstr name, cstr file, i32 line);

/// <summary>
/// logs and returns an error for when a null required parameter is not null
/// </summary>
/// <param name="name">name of the non-null parameter</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_PARAM_NOTNULL</returns>
err_t error_param_notnull(cstr name, cstr file, i32 line);

/// <summary>
/// logs and returns an error for an unnormalized floating points passed during color initialization or creation
/// </summary>
/// <param name="name">name of the unnormalized color component</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_color_unnorm(cstr name, cstr file, i32 line);

/// <summary>
/// logs and returns an error for an unopenable file
/// </summary>
/// <param name="path">path of the file</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_unopenable_file(cstr path, cstr file, i32 line);

/// <summary>
/// logs and returns an error for an uncloseable file
/// </summary>
/// <param name="path">path of the file</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_uncloseable_file(cstr path, cstr file, i32 line);

/// <summary>
/// logs and returns an error for while their is a size discrepancy
/// </summary>
/// <param name="size_a">first size</param>
/// <param name="size_b">second size</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_size_mismatch(u64 size_a, u64 size_b, cstr file, i32 line);

#endif