#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "reader.h"

int program_load(const char* path, const char* name, u32* program, ShaderType type)
{
	if (program == NULL)
	{
		printf("Cannot load shader program from unintialized pointer!\n");

		return -1;
	}

	*program = glCreateProgram();

	char full_path[BUFFER_SIZE];

	strcpy_s(full_path, BUFFER_SIZE, path);
	strcat_s(full_path, BUFFER_SIZE, "/");
	strcat_s(full_path, BUFFER_SIZE, name);

	u64 len = strlen(full_path);

	if (len + SHADER_EXT_LENGTH > 512)
	{
		printf("File path is too long!\n");

		return -1;
	}

	u32 shaders[6] = { 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 6; i++)
	{
		ShaderType current = (ShaderType)1 << i;

		if ((type & current) == 0) continue;

		shader_create(&shaders[i], current);

		if (shader_load(full_path, &shaders[i], current) < 0)
		{
			for (; i > 0; i--)
			{
				ShaderType current = (ShaderType)1 << i;

				if ((type & current) == 0) continue;


				glDeleteShader(shaders[i]);
				shaders[i] = 0;
			}

			return -1;
		}

		glAttachShader(*program, shaders[i]);
	}

	glLinkProgram(*program);

	for (int i = 0; i < 6; i++)
	{
		ShaderType current = (ShaderType)1 << i;

		if ((type & current) == 0) continue;

		if (shaders[i] != 0) glDeleteShader(shaders[i]);
	}

	int success;
	char infoLog[LOG_SIZE];

	glGetProgramiv(*program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(*program, LOG_SIZE, NULL, infoLog);
		printf("Failed to link shader program:\n%s\n", infoLog);

		return -1;
	}

	return 0;
}

int program_delete(u32 program)
{
	glDeleteProgram(program);

	return 0;
}

int shader_load(const char* path, u32* shader, ShaderType type)
{
	if (shader == NULL)
	{
		printf("Cannot load shader from unintialized pointer!\n");

		return -1;
	}

	char full_path[BUFFER_SIZE];

	strcpy_s(full_path, BUFFER_SIZE, path);

	if (append_extension(full_path, BUFFER_SIZE, type) < 0) return -1;

	char* contents = NULL;

	if (reader_string(full_path, &contents) < 0 || contents == NULL)
	{
		printf("Failed to read shader file!\n");

		if (contents != NULL) free(contents);

		return -1;
	}

	glShaderSource(*shader, 1, &contents, NULL);
	glCompileShader(*shader);

	free(contents);
	contents = NULL;

	int success;
	char infoLog[LOG_SIZE];

	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(*shader, LOG_SIZE, NULL, infoLog);
		printf("Compilation of shader program failed:\n%s\n", infoLog);

		return -1;
	}

	return 0;
}

int shader_create(u32* shader, ShaderType type)
{
	if (shader == NULL)
	{
		printf("Cannot create shader from uninitialized pointer!\n");

		return -1;
	}

	switch (type)
	{
	case SHADER_VERTEX:
		*shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case SHADER_TESSCNTRL:
		*shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case SHADER_TESSEVAL:
		*shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	case SHADER_GEOMETRY:
		*shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case SHADER_FRAGMENT:
		*shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case SHADER_COMPUTE:
		*shader = glCreateShader(GL_COMPUTE_SHADER);
		break;

	default:
		printf("Failed to determine shader type!\n");

		return -1;
	}

	return 0;
}

int append_extension(char* buffer, u64 bufferSize, ShaderType type)
{
	const char* extension = "";

	switch (type)
	{
	case SHADER_VERTEX:
		extension = ".vert";
		break;
	case SHADER_TESSCNTRL:
		extension = ".tesc";
		break;
	case SHADER_TESSEVAL:
		extension = ".tese";
		break;
	case SHADER_GEOMETRY:
		extension = ".geom";
		break;
	case SHADER_FRAGMENT:
		extension = ".frag";
		break;
	case SHADER_COMPUTE:
		extension = ".comp";
		break;

	default:
		printf("Failed to determine file extension!\n");

		return -1;
	}

	strcat_s(buffer, BUFFER_SIZE, extension);

	return 0;
}

int program_activate(u32 shader)
{
	if (!shader)
	{
		printf("Shader program is uninitialized!\n");

		return -1;
	}

	glUseProgram(shader);

	return 0;
}

void uniform_u32_set(u32 program, const char* name, u32 value)
{
	glUniform1ui(glGetUniformLocation(program, name), value);
}

void uniform_i32_set(u32 program, const char* name, i32 value)
{
	glUniform1i(glGetUniformLocation(program, name), value);
}

void uniform_float_set(u32 program, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(program, name), value);
}
