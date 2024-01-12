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

	u64 size = BUFFER_SIZE;

	*content = (str)malloc(size);

	if (*content == NULL) return error_alloc_fail("str", size, __FILE__, __LINE__);

	u64 length = 0;

	int ch = 0;

	while (ch != EOF)
	{
		ch = fgetc(ptr); ++length;

		*content[length] = (char)ch;

		if (length >= size - 1)
		{
			size *= 2; void* reallocation = (str)realloc(*content, size);

			if (reallocation == NULL)
			{
				free(*content);

				return error_alloc_fail("str", size, __FILE__, __LINE__);
			}
		}
	}

	str reallocation = (str)realloc(*content, length + 1);

	if (reallocation == NULL)
	{
		free(*content);

		return error_alloc_fail("str", length + 1, __FILE__, __LINE__);
	}

	*content = reallocation;

	*content[length] = '\0';

	if (fclose(ptr) < 0) return error_uncloseable_file(path, __FILE__, __LINE__);

	return 0;
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
