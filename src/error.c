#include "typedef.h"
#include "error.h"

#include <stdio.h>

err_t error_color_unnorm(const char* name, const char* file, int line) { printf("ERROR (%s, line %d): %s component of color was passed unnormalized float!", file, line, name); return ERROR_COLOR_UNNORM; }
err_t error_param_null(const char* name, const char* file, int line) { printf("ERROR (%s, line %d): parameter %s cannot be null!", file, line, name); return ERROR_PARAM_NULL; }
err_t error_alloc_fail(const char* type, u64 size, const char* file, int line) { printf("ERROR (%s, line %d): failed to allocate memory for %s of size %llu!", file, line, type, size); return ERROR_ALLOC_FAIL; }
