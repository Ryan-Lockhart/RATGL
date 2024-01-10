#ifndef SHADER_H

#define SHADER_H

#include "typedef.h"

#define SHADER_EXT_LENGTH 5

typedef enum ShaderType
{
	SHADER_VERTEX = 1 << 0,
	SHADER_TESSCNTRL = 1 << 1,
	SHADER_TESSEVAL = 1 << 2,
	SHADER_GEOMETRY = 1 << 3,
	SHADER_FRAGMENT = 1 << 4,
	SHADER_COMPUTE = 1 << 5,
} ShaderType;

int program_load(const char* path, const char* name, u32* program, ShaderType types);
int program_delete(u32 program);

int program_activate(u32 shader);

int shader_create(u32* shader, ShaderType type);
int shader_load(const char* path, u32* shader, ShaderType type);

int append_extension(char* buffer, u64 bufferSize, ShaderType type);

#endif
