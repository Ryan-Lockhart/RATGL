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

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int WINDOW_WIDTH_HALF = 640 / 2;
const int WINDOW_HEIGHT_HALF = 480 / 2;

static GLFWwindow* window;
static vertex_array_t vertex_array;
static u32 square_shader;
static u32 glyph_texture;

void framebufferReizeCallback(GLFWwindow* window, int width, int height);

int glfwSetWindowCenter(GLFWwindow* window);

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

err_t reserialize_test()
{
    err_t err = ERROR_NONE;

    byte* vertex_byte_buffer = NULL;

    err |= serialize_vec3s(&vertex_byte_buffer, vertices, sizeof(vertices) / sizeof(vec3_t));
    if (err != ERROR_NONE) return err;

    err |= writer_binary("data/arrays/cube.vertices", vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= reader_binary("data/arrays/cube.vertices", &vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    vec3_t* vertex_buffer = NULL;
    u64 vertex_buffer_size;

    err |= deserialize_vec3s(&vertex_buffer, &vertex_buffer_size, vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= buffer_destroy(&vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    for (int i = 0; i < vertex_buffer_size; ++i)
        printf("[%f, %f, %f]%s", vertex_buffer[i].x, vertex_buffer[i].y, vertex_buffer[i].z, i < vertex_buffer_size ? ",\n" : "\n\n");

    byte* index_byte_buffer = NULL;

    err |= serialize_u32s(&index_byte_buffer, indices, sizeof(indices) / sizeof(u32));
    if (err != ERROR_NONE) return err;

    err |= writer_binary("data/arrays/cube.indices", index_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= reader_binary("data/arrays/cube.indices", &index_byte_buffer);
    if (err != ERROR_NONE) return err;

    u32* index_buffer = NULL;
    u64 index_buffer_size;

    err |= deserialize_u32s(&index_buffer, &index_buffer_size, index_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= buffer_destroy(&index_byte_buffer);
    if (err != ERROR_NONE) return err;

    for (int i = 0; i < index_buffer_size; ++i)
        printf("%u%s", index_buffer[i], i < index_buffer_size ? ",\n" : "\n\n");

    return ERROR_NONE;
}

err_t load_window()
{
    if (glfwInit() == GLFW_FALSE) return error_glfw_init_fail(__FILE__, __LINE__);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RATGL", NULL, NULL);

    if (window == NULL) return error_window_init_fail(__FILE__, __LINE__);

    glfwSetWindowCenter(window);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);

        glfwTerminate();

        return error_glad_init_fail(__FILE__, __LINE__);
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebufferReizeCallback);

    return ERROR_NONE;
}

err_t load_shaders()
{
    err_t err = ERROR_NONE;

    err |= program_load("data/shaders", "basic_shader", &square_shader, SHADER_VERTEX | SHADER_FRAGMENT);
    if (err != ERROR_NONE) return err;

    return ERROR_NONE;
}

err_t load_arrays()
{
    err_t err = ERROR_NONE;

    byte* vertex_byte_buffer = NULL;

    err |= reader_binary("data/arrays/cube.vertices", &vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    vec3_t* vertex_buffer = NULL;
    u64 vertex_buffer_size;

    err |= deserialize_vec3s(&vertex_buffer, &vertex_buffer_size, vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= buffer_destroy(&vertex_byte_buffer);
    if (err != ERROR_NONE) return err;

    byte* index_byte_buffer = NULL;

    err |= reader_binary("data/arrays/cube.indices", &index_byte_buffer);
    if (err != ERROR_NONE) return err;

    u32* index_buffer = NULL;
    u64 index_buffer_size;

    err |= deserialize_u32s(&index_buffer, &index_buffer_size, index_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= buffer_destroy(&index_byte_buffer);
    if (err != ERROR_NONE) return err;

    err |= vertex_array_create(&vertex_array, 0, vertex_buffer, vertex_buffer_size, index_buffer, index_buffer_size);
    if (err != ERROR_NONE) return err;

    free(vertex_buffer);
    free(index_buffer);
}

err_t initialize()
{
    err_t err = ERROR_NONE;

    err |= load_window(); if (err != ERROR_NONE) return err;

    err |= load_shaders(); if (err != ERROR_NONE) return err;

    err |= load_arrays(); if (err != ERROR_NONE) return err;

    return ERROR_NONE;
}

err_t input()
{
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

    return ERROR_NONE;
}

err_t update()
{
    return ERROR_NONE;
}

err_t render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    program_activate(square_shader);

    vertex_array_activate(&vertex_array);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vertex_array_deactive();

    glfwSwapBuffers(window);

    return ERROR_NONE;
}

err_t terminate()
{
    vertex_array_delete(&vertex_array);

    program_delete(square_shader);

    glfwDestroyWindow(window);

    glfwTerminate();

    return ERROR_NONE;
}

int closing() { return glfwWindowShouldClose(window); }

err_t main(void)
{
    initialize();

    forever {
        if (closing())
            break;

        input();
        update();
        render();        
    }

    terminate();

    return ERROR_NONE;
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
