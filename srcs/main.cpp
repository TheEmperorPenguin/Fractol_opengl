/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-29 14:42:22                                       *
*******************************************************************************/

#include "scop.hpp"

unsigned int    triangle1;
unsigned int    triangle2;
Shader * ourShader;
float offset = 0.0f;
float x_pos = 0.0f;
float y_pos = 0.0f;
float zoom = 1.0f;

void display(GLFWwindow* window)
{
    draw_triangle(&triangle1, 9);
    draw_triangle(&triangle2, 9);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        exit(42);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        y_pos += 0.01f * zoom;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        y_pos -= 0.01f * zoom;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        x_pos -= 0.01f * zoom;
    if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        x_pos += 0.01f * zoom;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        zoom -= 0.01f * zoom;
    if (glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS)
        zoom += 0.01f * zoom;

    offset += 0.001;
    (*ourShader).setFloat("time", sin(offset));
    (*ourShader).setFloat("x_pos", x_pos);
    (*ourShader).setFloat("y_pos", y_pos);
    if(zoom < 0.00001f)
        zoom = 0.00001f;
    (*ourShader).setFloat("zoom", zoom);
    (*ourShader).setFloat("resolution", WINDOW_WIDTH, WINDOW_HEIGHT);
}

void create_scene()
{        
    ourShader = new Shader("srcs/ArcticFeather/shaders/vertex.glsl", "srcs/ArcticFeather/shaders/mandelbrot.glsl");
    (*ourShader).use();
    
    float vertic1[] = {
        -1.f, -1.f, 0.0f,
        -1.f, 1.f, 0.0f,
        1.f, -1.f, 0.0f
    };
    triangle1 = triangle(vertic1, sizeof(vertic1));
        float vertic2[] = {
        1.f, 1.f, 0.0f,
        -1.f, 1.f, 0.0f,
        1.f, -1.f, 0.0f
    };
    triangle2 = triangle(vertic2, sizeof(vertic2));

}

void keypress( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    (void)window;
    (void)mods;
    (void)scancode;
    (void)action;
    (void)key;


}

int main(int argc, char** argv) {
    AF_init(WINDOW_HEIGHT, WINDOW_WIDTH, "Scop Gtouzali", &create_scene, &display, &keypress);
    AF_destroy();
}
