#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "typedef.h"

#include "writer.h"
#include "reader.h"

#include "serializer.h"
#include "deserializer.h"

#include "shader.h"
#include "vertex_array.h"

#include "vec3.h"

#include "color.h"

#ifdef _DEBUG
#define main main
#else
#define main WinMain
#endif

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void framebufferReizeCallback(GLFWwindow* window, int width, int height);

int glfwSetWindowCenter(GLFWwindow* window);

void processInput(GLFWwindow* window);

vec3_t vertices[] =
{
    {  1.0f,  1.0f, 0.0f },
    {  1.0f, -1.0f, 0.0f },
    { -1.0f, -1.0f, 0.0f },
    { -1.0f,  1.0f, 0.0f }
};

u32 indices[] =
{
    0, 1, 3,
    1, 2, 3
};

int main(void)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwSetWindowCenter(window);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");

        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebufferReizeCallback);

    u32 shaderProgram;

    if (program_load("shaders", "basic_shader", &shaderProgram, SHADER_VERTEX | SHADER_FRAGMENT) < 0)
    {
        printf("Failed to load shader program:\nbasic_shader\n");

        return -1;
    }

    byte* vertex_byte_buffer;

    reader_binary("cube.vertices", &vertex_byte_buffer);

    vec3_t* vertex_buffer;
    u64 vertex_buffer_size;

    deserialize_floats(&vertex_buffer, &vertex_buffer_size, vertex_byte_buffer);
    free(vertex_byte_buffer);

    byte* index_byte_buffer;

    reader_binary("cube.indices", &index_byte_buffer);

    u32* index_buffer;
    u64 index_buffer_size;

    deserialize_u32s(&index_buffer, &index_buffer_size, index_byte_buffer);
    free(index_byte_buffer);

    vertex_array_t vertex_array;

    vertex_array_create(&vertex_array, 0, vertex_buffer, vertex_buffer_size, index_buffer, index_buffer_size);

    free(vertex_buffer);
    free(index_buffer);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program_activate(shaderProgram);

        vertex_array_activate(&vertex_array);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        vertex_array_deactive();

        glfwSwapBuffers(window);
    }

    vertex_array_delete(&vertex_array);

    program_delete(shaderProgram);

    glfwTerminate();

    return 0;
}

void framebufferReizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int glfwSetWindowCenter(GLFWwindow* window)
{
    if (!window) return -1;

    int sx = 0, sy = 0;
    int px = 0, py = 0;
    int mx = 0, my = 0;
    int monitor_count = 0;
    int best_area = 0;
    int final_x = 0, final_y = 0;

    glfwGetWindowSize(window, &sx, &sy);
    glfwGetWindowPos(window, &px, &py);

    GLFWmonitor** m = glfwGetMonitors(&monitor_count);

    if (!m) return -1;

    for (int j = 0; j < monitor_count; ++j)
    {
        glfwGetMonitorPos(m[j], &mx, &my);
        const GLFWvidmode* mode = glfwGetVideoMode(m[j]);
        if (!mode) continue;

        int minX = max(mx, px);
        int minY = max(my, py);

        int maxX = min(mx + mode->width, px + sx);
        int maxY = min(my + mode->height, py + sy);

        int area = max(maxX - minX, 0) * max(maxY - minY, 0);

        if (area > best_area)
        {
            final_x = mx + (mode->width - sx) / 2;
            final_y = my + (mode->height - sy) / 2;

            best_area = area;
        }
    }

    if (best_area) glfwSetWindowPos(window, final_x, final_y);
    else
    {
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        if (primary)
        {
            const GLFWvidmode* desktop = glfwGetVideoMode(primary);

            if (desktop)
                glfwSetWindowPos(window, (desktop->width - sx) / 2, (desktop->height - sy) / 2);
            else return -1;
        }
        else return -1;
    }

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}
