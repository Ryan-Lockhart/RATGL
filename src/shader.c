#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "reader.h"

str shader_fetch_name(shader_t type)
{
	switch (type)
	{
		case SHADER_VERTEX: return "vertex shader";
		case SHADER_TESSCNTRL: return "tesscntrl shader";
		case SHADER_TESSEVAL: return "tesseval shader";
		case SHADER_GEOMETRY: return "geometry shader";
		case SHADER_FRAGMENT: return "fragment shader";
		case SHADER_COMPUTE: return "compute shader";

		default: return "unknown shader";
	}
}

str shader_fetch_ext(shader_t type)
{
	switch (type)
	{
		case SHADER_VERTEX: return ".vert";
		case SHADER_TESSCNTRL: return ".tesc";
		case SHADER_TESSEVAL: return ".tese";
		case SHADER_GEOMETRY: return ".geom";
		case SHADER_FRAGMENT: return ".frag";
		case SHADER_COMPUTE: return ".comp";

		default: return ".unkn";
	}
}

err_t path_create(str* buffer, cstr path, cstr name)
{
	if (buffer == NULL) return error_param_null("buffer", __FILE__, __LINE__);
	if (*buffer != NULL) return error_param_notnull("*buffer", __FILE__, __LINE__);

	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (name == NULL) return error_param_null("name", __FILE__, __LINE__);

	u64 path_len = strlen(path);
	u64 name_len = strlen(name);

	u64 full_len = path_len + name_len + 2;

	*buffer = (str)malloc(full_len);

	if (*buffer == NULL) return error_alloc_fail("str", full_len, __FILE__, __LINE__);

	memset(*buffer, '\0', full_len);
	memcpy(*buffer, path, path_len);
	memset(*buffer + path_len, '/', 1);
	memcpy(*buffer + path_len + 1, name, name_len);

	return ERROR_NONE;
}

err_t path_append_ext(str* path, cstr ext)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (*path == NULL) return error_param_null("*path", __FILE__, __LINE__);

	if (ext == NULL) return error_param_null("ext", __FILE__, __LINE__);

	u64 path_len = strlen(path);
	u64 ext_len = strlen(ext);

	u64 full_len = path_len + ext_len + 1;

	memory reall = realloc(*path, full_len);

	if (reall == NULL) return error_alloc_fail("str", full_len, __FILE__, __LINE__);

	*path = (str)reall;

	memcpy(*path + path_len, ext, ext_len);
	memset(*path + path_len + ext_len, '\0', 1);

	return ERROR_NONE;
}

err_t path_destroy(str* path)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (*path == NULL) return error_param_null("*path", __FILE__, __LINE__);

	free(*path);
	*path = NULL;

	return ERROR_NONE;
}

err_t program_load(cstr path, cstr name, u32* program, shader_t type)
{
	if (program == NULL) return error_param_null("program", __FILE__, __LINE__);
	if (*program != 0) return error_param_notnull("*program", __FILE__, __LINE__);

	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (name == NULL) return error_param_null("name", __FILE__, __LINE__);

	*program = glCreateProgram();

	

	u32 shaders[6] = { 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 6; i++)
	{
		shader_t current = (shader_t)1 << i;

		if ((type & current) == 0) continue;

		shader_create(&shaders[i], current);

		if (shader_load(full_path, &shaders[i], current) < 0)
		{
			for (; i > 0; i--)
			{
				shader_t current = (shader_t)1 << i;

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
		shader_t current = (shader_t)1 << i;

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

void program_delete(u32 program)
{
	glDeleteProgram(program);
}

err_t program_activate(u32 shader)
{
	if (shader == 0) return error_param_null("shader", __FILE__, __LINE__);

	glUseProgram(shader);

	return ERROR_NONE;
}

err_t shader_load(cstr path, u32* shader, shader_t type)
{
	err_t err = ERROR_NONE;

	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);

	if (shader == NULL) return error_param_null("shader", __FILE__, __LINE__);
	if (*shader == 0) return error_param_null("*shader", __FILE__, __LINE__);

	if (type == 0) return error_param_null("type", __FILE__, __LINE__);

	char full_path[BUFFER_SIZE];

	strcpy_s(full_path, BUFFER_SIZE, path);

	err |= path_append_ext(full_path, BUFFER_SIZE, type); if (err < 0) return err;

	char* contents = NULL;

	err |= reader_string(full_path, &contents); if (err < 0) return err;

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

	return ERROR_NONE;
}

err_t shader_create(u32* shader, shader_t type)
{
	if (shader == NULL) return error_param_null("shader", __FILE__, __LINE__);

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

		default: return error_unknown_enum("ShaderType", (i32)type, __FILE__, __LINE__);
	}

	return ERROR_NONE;
}

err_t uniform_u32_set(u32 program, const char* name, u32 value)
{
	glUniform1ui(glGetUniformLocation(program, name), value);

	return ERROR_NONE;
}

err_t uniform_i32_set(u32 program, const char* name, i32 value)
{
	glUniform1i(glGetUniformLocation(program, name), value);

	return ERROR_NONE;
}

err_t uniform_float_set(u32 program, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(program, name), value);

	return ERROR_NONE;
}
