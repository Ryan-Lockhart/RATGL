#include "error.h"

#include <stdio.h>
#include <time.h>

void time_log(void)
{
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	printf("[%d:%d:%d]", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}

err_t error_alloc_fail(cstr type, u64 size, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to allocate memory for %s of size %llu!\n", file, line, type, size);

	return ERROR_ALLOC_FAIL;
}

err_t error_param_null(cstr name, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): parameter %s cannot be null!\n", file, line, name);

	return ERROR_PARAM_NULL;
}

err_t error_param_notnull(cstr name, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): parameter %s must be null!\n", file, line, name);

	return ERROR_PARAM_NOTNULL;
}

err_t error_color_unnorm(cstr name, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): %s component of color was passed unnormalized float!\n", file, line, name);

	return ERROR_COLOR_UNNORM;
}

err_t error_unopenable_file(cstr path, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to open file %s!\n", file, line, path);

	return ERROR_UNOPENABLE_FILE;
}

err_t error_uncloseable_file(cstr path, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to close file %s!\n", file, line, path);

	return ERROR_UNCLOSEABLE_FILE;
}

err_t error_size_mismatch(u64 size_a, u64 size_b, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): size of %llu does not match size of %llu!\n", file, line, size_a, size_b);

	return ERROR_SIZE_MISMATCH;
}

err_t error_image_load(cstr message, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to load image! (%s)\n", file, line, message);

	return ERROR_IMAGE_LOAD;
}

err_t error_not_power_of_two(cstr name, u64 size, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): %s is not a power of two! (%llu)\n", file, line, name, size);

	return ERROR_NON_POWER_OF_TWO;
}

err_t error_size_indivisible(u64 size_a, u64 size_b, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): size of %llu is not divisible by %llu!\n", file, line, size_a, size_b);

	return ERROR_SIZE_MISMATCH;
}

err_t error_window_init_fail(cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to initialize the main window!\n", file, line);

	return ERROR_WINDOW_INIT_FAIL;
}

err_t error_glad_init_fail(cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): failed to initialize GLAD!\n", file, line);

	return ERROR_GLAD_INIT_FAIL;
}

err_t error_unknown_enum(cstr type, i32 value, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): enum %s does not contain value of %d!\n", type, value, file, line);

	return ERROR_UNKNOWN_ENUM;
}

err_t error_shader_compil_fail(str message, cstr file, i32 line)
{
	time_log(); printf(" - ERROR (%s, line %d): opengl failed to compile shader program! (%s)\n", file, line, message);

	return ERROR_UNKNOWN_ENUM;
}
