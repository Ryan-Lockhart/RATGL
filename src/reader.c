#include "reader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int reader_string(const char* path, char** content)
{
	u64 str_size, read_size;
	*content = NULL;

	FILE* ptr;

	if (fopen_s(&ptr, path, "rb") != 0)
	{
		printf("Failed to open file: %s\n", path);

		return -1;
	}

	fseek(ptr, 0, SEEK_END);
	str_size = (u64)ftell(ptr) + 1;

	fclose(ptr);

	if (fopen_s(&ptr, path, "r") != 0)
	{
		printf("Failed to open file: %s\n", path);

		return -1;
	}

	void* mem = malloc(str_size);

	if (mem == NULL)
	{
		printf("Failed to allocate memory during file read!\n");

		return -1;
	}

	*content = memset(mem, '\0', str_size);

	if (*content == NULL)
	{
		printf("Failed to allocate memory during file read!\n");
		return -1;
	}

	read_size = fread(*content, sizeof(char), str_size - 1, ptr);

	fclose(ptr);

	return 0;
}

int reader_binary(const char* path, byte** buffer)
{
	FILE* ptr;

	if (fopen_s(&ptr, path, "rb") != 0)
	{
		printf("Failed to open file: %s\n", path);

		return -1;
	}

	fseek(ptr, 0, SEEK_END);
	u64 size = (u64)ftell(ptr);
	rewind(ptr);

	*buffer = malloc(size);

	if (*buffer == NULL)
	{
		printf("Failed to allocate memory during file read!\n");

		return -1;
	}

	fread(*buffer, BYTE_SIZE, size / BYTE_SIZE, ptr);

	fclose(ptr);

	return 0;
}
