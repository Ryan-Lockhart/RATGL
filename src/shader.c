#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "reader.h"

cstr shader_fetch_name(shader_t type)
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

cstr shader_fetch_ext(shader_t type)
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

err_t path_create(str* path, cstr base, cstr name)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (*path != NULL) return error_param_notnull("*path", __FILE__, __LINE__);

	if (base == NULL) return error_param_null("base", __FILE__, __LINE__);
	if (name == NULL) return error_param_null("name", __FILE__, __LINE__);

	u64 path_len = strlen(base);
	u64 name_len = strlen(name);

	u64 full_len = path_len + name_len + 2;

	*path = (str)malloc(full_len);

	if (*path == NULL) return error_alloc_fail("str", full_len, __FILE__, __LINE__);

	strcpy_s(*path, full_len, base);
	strcat_s(*path, full_len, "/");
	strcat_s(*path, full_len, name);

	return ERROR_NONE;
}

err_t path_append_ext(str* path, cstr base, cstr ext)
{
	if (path == NULL) return error_param_null("path", __FILE__, __LINE__);
	if (*path != NULL) return error_param_notnull("*path", __FILE__, __LINE__);

	if (base == NULL) return error_param_null("base", __FILE__, __LINE__);
	if (ext == NULL) return error_param_null("ext", __FILE__, __LINE__);

	u64 base_len = strlen(base);
	u64 ext_len = strlen(ext);

	u64 path_len = base_len + ext_len + 1;

	*path = (str)malloc(path_len);

	if (*path == NULL) return error_alloc_fail("str", path_len, __FILE__, __LINE__);

	strcpy_s(*path, path_len, base);
	strcat_s(*path, path_len, ext);

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

	err_t err = ERROR_NONE;

	*program = glCreateProgram();

	str partial_path = NULL;
	path_create(&partial_path, path, name);

	u32 shaders[MAX_SHADERS] = { 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < MAX_SHADERS; ++i)
	{
		shader_t current = (shader_t)1 << i;

		if ((type & current) == 0) continue;

		shader_create(&shaders[i], current);

		if (err = shader_load(partial_path, &shaders[i], current) != ERROR_NONE)
		{
			for (; i > 0; --i)
			{
				shader_t current = (shader_t)1 << i;

				if ((type & current) == 0) continue;

				glDeleteShader(shaders[i]);
				shaders[i] = 0;
			}

			path_destroy(&partial_path);
			glDeleteProgram(*program);

			return err;
		}

		glAttachShader(*program, shaders[i]);
	}

	path_destroy(&partial_path);

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
		return error_shader_link_fail(infoLog, __FILE__, __LINE__);
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

	str full_path = NULL;

	if (err = path_append_ext(&full_path, path, shader_fetch_ext(type)) != ERROR_NONE) return err;

	char* contents = NULL;

	if (err = reader_string(full_path, &contents) != ERROR_NONE)
	{
		path_destroy(&full_path);

		return err;
	}

	path_destroy(&full_path);

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
		return error_shader_compil_fail(infoLog, __FILE__, __LINE__);
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
