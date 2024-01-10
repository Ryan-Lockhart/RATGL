#include "vertex_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int vertex_array_create(vertex_array_t* vao, u32 index, const float* vertices, u64 verticesSize, const u32* indices, u64 indicesSize)
{
	if (vao == NULL || vertices == NULL || indices == NULL)
	{
		printf("Vertex array cannot be uninitialized!\n");

		return -1;
	}

	glGenVertexArrays(1, &vao->vao);
	
	glBindVertexArray(vao->vao);

	if (vertex_buffer_create(&vao->vbo, vertices, verticesSize) < 0)
	{
		printf("Vertex buffer could not be created!\n");

		glDeleteVertexArrays(1, &vao->vao);

		return -1;
	}

	if (element_buffer_create(&vao->ebo, indices, indicesSize) < 0)
	{
		printf("Vertex buffer could not be created!\n");

		glDeleteVertexArrays(1, &vao->vao);
		glDeleteBuffers(1, &vao->vbo);

		return -1;
	}

	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);

	return 0;
}

int vertex_buffer_create(u32* vbo, const float* vertices, u64 verticesSize)
{
	if (vbo == NULL || vertices == NULL)
	{
		printf("Vertex buffer cannot be uninitialized!\n");

		return -1;
	}

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices, GL_STATIC_DRAW);

	return 0;
}

int element_buffer_create(u32* ebo, const u32* indices, u64 indicesSize)
{
	if (ebo == NULL || indices == NULL)
	{
		printf("Element buffer cannot be uninitialized!\n");

		return -1;
	}

	glGenBuffers(1, ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(u32), indices, GL_STATIC_DRAW);

	return 0;
}

int vertex_array_delete(vertex_array_t* vao)
{
	if (vao == NULL)
	{
		printf("Vertex array is uninitialized!\n");

		return -1;
	}

	glDisableVertexAttribArray(vao->index);

	glDeleteBuffers(1, &vao->ebo);
	glDeleteBuffers(1, &vao->vbo);

	glDeleteVertexArrays(1, &vao->vao);

	return 0;
}

int vertex_array_activate(const vertex_array_t* vao)
{
	glBindVertexArray(vao->vao);

	return 0;
}

int vertex_array_deactive()
{
	glBindVertexArray(0);

	return 0;
}
