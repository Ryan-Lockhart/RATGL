#ifndef SHADER_H

#define SHADER_H

#include "error.h"

// length of the shader file extension (.xxxx)
#define SHADER_EXT_LENGTH 5

typedef enum shader_t
{
	SHADER_VERTEX = 1 << 0,
	SHADER_TESSCNTRL = 1 << 1,
	SHADER_TESSEVAL = 1 << 2,
	SHADER_GEOMETRY = 1 << 3,
	SHADER_FRAGMENT = 1 << 4,
	SHADER_COMPUTE = 1 << 5,
} shader_t;

#define MAX_SHADERS 6

/// <summary>
/// fetches the cstr name of the shader type
/// </summary>
/// <param name="type">- type of the shader</param>
/// <returns>cstr name of the shader type</returns>
cstr shader_fetch_name(shader_t type);

/// <summary>
/// fetches the cstr extension of the shader type
/// </summary>
/// <param name="type">- type of the shader</param>
/// <returns>cstr extension of the shader type</returns>
cstr shader_fetch_ext(shader_t type);

/// <summary>
/// creates a partial path from a base path and name
/// </summary>
/// <param name="buffer">character buffer to store the full path</param>
/// <param name="path"></param>
/// <param name="name"></param>
/// <returns></returns>
err_t path_create(str* path, cstr base, cstr name);

/// <summary>
/// appends the appropriate shader file extension to a partial path
/// </summary>
/// <param name="path">- partial path</param>
/// <param name="ext">- base path of file</param>
/// <param name="ext">- extension to append</param>
/// <returns>ERROR_NONE on success; ERROR_PARAM_NULL or ERROR_UNKNOWN_ENUM on failure</returns>
err_t path_append_ext(str* path, cstr base, cstr ext);

/// <summary>
/// destroys a path
/// </summary>
/// <param name="path">address of the path</param>
/// <returns>ERROR_NONE on success; ERROR_PARAM_NULL or ERROR_PARAM_NOTNULL on failure</returns>
err_t path_destroy(str* path);

/// <summary>
/// load a shader program by name and base path with shader types
/// </summary>
/// <param name="path">- base path of the shader program</param>
/// <param name="name">- name of the shader program</param>
/// <param name="program">- address of the shader program handle</param>
/// <param name="types">- shader types for this shader program</param>
/// <returns></returns>
err_t program_load(cstr path, cstr name, u32* program, shader_t types);

/// <summary>
/// unloads a shader program
/// </summary>
/// <param name="program">- shader program handle</param>
void program_delete(u32 program);

/// <summary>
/// activates a shader program for rendering
/// </summary>
/// <param name="program">- shader program handle</param>
/// <returns>ERROR_NONE on success; ERROR_PARAM_NULL on failure</returns>
err_t program_activate(u32 program);

/// <summary>
/// generates an opengl shader handle
/// </summary>
/// <param name="shader">- address of the handle</param>
/// <param name="type">- type of the shader</param>
/// <returns>ERROR_NONE on success; ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL, or ERROR_UNKNOWN_ENUM on failure</returns>
err_t shader_create(u32* shader, shader_t type);

/// <summary>
/// creates an opengl shader handle and loads it with a shader source file
/// </summary>
/// <param name="path">- path of the shader file</param>
/// <param name="shader">- address of the handle</param>
/// <param name="type">- type of the shader</param>
/// <returns>ERROR_NONE on success; ERROR_PARAM_NULL, ERROR_PARAM_NOTNULL, or ERROR_UNKNOWN_ENUM on failure</returns>
err_t shader_load(cstr path, u32* shader, shader_t type);

#endif
