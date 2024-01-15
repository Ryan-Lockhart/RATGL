#include "reader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int reader_string(cstr path, str* content)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (content == NULL) return error_param_null("content", __FILE__, __LINE__);

	if (*content != NULL) return error_param_notnull("*content", __FILE__, __LINE__);

	FILE* ptr = NULL;

	if (fopen_s(&ptr, path, "r") != 0) return error_unopenable_file(path, __FILE__, __LINE__);

	fseek(ptr, 0, SEEK_END);
	u64 str_size = (u64)ftell(ptr);
	rewind(ptr);

	*content = (str)malloc(str_size);

	if (*content == NULL) return error_alloc_fail("str", str_size, __FILE__, __LINE__);

	memset(*content, '\0', str_size);

	u64 read_size = fread(*content, sizeof(char), str_size, ptr);

	if (str_size != read_size)
	{
		void* trunc = realloc(*content, read_size + 1);

		if (trunc == NULL)
		{
			free(*content);

			return error_alloc_fail("str", read_size + 1, __FILE__, __LINE__);
		}

		*content = (str)trunc;
	}

	if (fclose(ptr) < 0)
	{
		free(*content);

		return error_uncloseable_file(path, __FILE__, __LINE__);
	}

	return ERROR_NONE;
}

int reader_binary(cstr path, byte** buffer)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);

	if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

	FILE* ptr = NULL;

	if (fopen_s(&ptr, path, "rb") != 0) return error_unopenable_file(path, __FILE__, __LINE__);

	fseek(ptr, 0, SEEK_END);
	u64 byte_size = (u64)ftell(ptr);
	rewind(ptr);

	*buffer = malloc(byte_size);

	if (*buffer == NULL) return error_alloc_fail("byte", byte_size, __FILE__, __LINE__);

	u64 read_size = fread(*buffer, BYTE_SIZE, byte_size / BYTE_SIZE, ptr);

	if (byte_size / BYTE_SIZE != read_size) return error_size_mismatch(byte_size, read_size, __FILE__, __LINE__);

	if (fclose(ptr) < 0) return error_uncloseable_file(path, __FILE__, __LINE__);

	return 0;
}
