#ifndef ERROR_H

#define ERROR_H

typedef enum err_t {
	ERROR_COLOR_UNNORM = -3,
	ERROR_PARAM_NULL = -2,
	ERROR_ALLOC_FAIL = -1,
	ERROR_NONE = 0,
} err_t;

/// <summary>
/// logs and returns an error for unnormalized floating points passed for color initialization or creation
/// </summary>
/// <param name="name">name of the unnormalized color component</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_COLOR_UNNORM</returns>
err_t error_color_unnorm(const char* name, const char* file, int line);

/// <summary>
/// logs and returns an error for when a non-null required parameter is null
/// </summary>
/// <param name="name">name of the null parameter</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_PARAM_NULL</returns>
err_t error_param_null(const char* name, const char* file, int line);

/// <summary>
/// logs and returns an error when a *alloc call fails to allocate memory
/// </summary>
/// <param name="type">type of the memory</param>
/// <param name="size">size of the memory</param>
/// <param name="file">file in which this error occured</param>
/// <param name="line">file at which this error occured</param>
/// <returns>ERROR_ALLOC_FAIL</returns>
err_t error_alloc_fail(const char* type, u64 size, const char* file, int line);

#endif