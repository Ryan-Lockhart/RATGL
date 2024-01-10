#include "writer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int writer_string(const char* path, const char* content)
{
	if (content == NULL)
	{
		printf("Cannot write to file, no content!\n");

		return -1;
	}

	FILE* ptr;

	if (fopen_s(&ptr, path, "w") != 0)
	{
		printf("Failed to open file: %s\n", path);

		return -1;
	}

	fwrite(content, sizeof(char), strlen(content), ptr);

	fclose(ptr);

	return 0;
}

int writer_binary(const char* path, const byte* buffer)
{
	if (buffer == NULL)
	{
		printf("Cannot write to file, no content!\n");

		return -1;
	}

	FILE* ptr;

	if (fopen_s(&ptr, path, "wb") != 0)
	{
		printf("Failed to open file: %s\n", path);

		return -1;
	}

	u64 write_count = fwrite(buffer, BYTE_SIZE, sizeof(buffer) * BYTE_SIZE, ptr);

	fclose(ptr);

	return 0;
}
