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
	ERROR_SIZE_INDIVISIBLE = -1 << 7,
	ERROR_IMAGE_LOAD = -1 << 8,
	ERROR_NON_POWER_OF_TWO = -1 << 9,
	ERROR_WINDOW_INIT_FAIL = -1 << 10,
	ERROR_GLAD_INIT_FAIL = -1 << 11,
	ERROR_UNKNOWN_ENUM = -1 << 12,
	ERROR_SHADER_COMPIL_FAIL = -1 << 13,
} err_t;

/// <summary>
/// logs the current time
/// </summary>
void time_log(void);

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
/// logs and returns an error for when their is a size discrepancy
/// </summary>
/// <param name="size_a">first size</param>
/// <param name="size_b">second size</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_size_mismatch(u64 size_a, u64 size_b, cstr file, i32 line);

/// <summary>
/// logs and returns an error for when a size is not divisible by another
/// </summary>
/// <param name="size_a">first size</param>
/// <param name="size_b">second size</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_size_indivisible(u64 size_a, u64 size_b, cstr file, i32 line);

/// <summary>
/// logs and returns an error for when SOIL fails to load an image
/// </summary>
/// <param name="message">message returned from SOIL</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_IMAGE_LOAD</returns>
err_t error_image_load(cstr message, cstr file, i32 line);

/// <summary>
/// logs and returns an error for when a size is not a power of two
/// </summary>
/// <param name="name">name of the non power of two parameter</param>
/// <param name="size">size of the non power of two parameter</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns></returns>
err_t error_not_power_of_two(cstr name, u64 size, cstr file, i32 line);

/// <summary>
/// logs and returns an error when the main window fails to initialize
/// </summary>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_WINDOW_INIT_FAIL</returns>
err_t error_window_init_fail(cstr file, i32 line);

/// <summary>
/// logs and returns an error when GLAD fails to initialize
/// </summary>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_GLAD_INIT_FAIL</returns>
err_t error_glad_init_fail(cstr file, i32 line);

/// <summary>
/// logs and returns an error when an unknown enum value is passed to a switch
/// </summary>
/// <param name="type">type of the enum</param>
/// <param name="value">unknown value of the enum</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_UNKNOWN_ENUM</returns>
err_t error_unknown_enum(cstr type, i32 value, cstr file, i32 line);

/// <summary>
/// logs and returns an error when opengl fails to compile a shader program
/// </summary>
/// <param name="message">error message from opengl</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_SHADER_COMPIL_FAIL</returns>
err_t error_shader_compil_fail(str message, cstr file, i32 line);

#endif