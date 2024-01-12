#include "writer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

err_t writer_string(cstr path, cstr content)
{
	FILE* ptr = NULL;

	if (content == NULL) return error_param_null("content", __FILE__, __LINE__);

	if (fopen_s(&ptr, path, "w") != 0) return error_unopenable_file(path, __FILE__, __LINE__);

	fwrite(content, sizeof(char), strlen(content), ptr);

	if (fclose(ptr) < 0) return error_uncloseable_file(path, __FILE__, __LINE__);

	return 0;
}

err_t writer_binary(cstr path, const byte* buffer)
{
	FILE* ptr = NULL;

	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

	if (fopen_s(&ptr, path, "wb") != 0) return error_unopenable_file(path, __FILE__, __LINE__);

	fwrite(buffer, BYTE_SIZE, sizeof(buffer) * BYTE_SIZE, ptr);

	if (fclose(ptr) < 0) return error_uncloseable_file(path, __FILE__, __LINE__);

	return 0;
}
