#include "error.h"

#include <stdio.h>

err_t error_alloc_fail(cstr type, u64 size, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): failed to allocate memory for %s of size %llu!\n", file, line, type, size);

	return ERROR_ALLOC_FAIL;
}

err_t error_param_null(cstr name, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): parameter %s cannot be null!\n", file, line, name);

	return ERROR_PARAM_NULL;
}

err_t error_param_notnull(cstr name, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): parameter %s must be null!\n", file, line, name);

	return ERROR_PARAM_NOTNULL;
}

err_t error_color_unnorm(cstr name, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): %s component of color was passed unnormalized float!\n", file, line, name);

	return ERROR_COLOR_UNNORM;
}

err_t error_unopenable_file(cstr path, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): failed to open file %s!\n", file, line, path);

	return ERROR_UNOPENABLE_FILE;
}

err_t error_uncloseable_file(cstr path, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): failed to close file %s!\n", file, line, path);

	return ERROR_UNCLOSEABLE_FILE;
}

err_t error_size_mismatch(u64 size_a, u64 size_b, cstr file, i32 line)
{
	printf("ERROR (%s, line %d): size of %llu does not match size of %llu!\n", file, line, size_a, size_b);

	return ERROR_SIZE_MISMATCH;
}
