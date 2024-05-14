/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-14 13:59:35                                       *
*******************************************************************************/

#include "scop.hpp"

Model * ratchet;
unsigned int    triangle1;
unsigned int    triangle2;
Shader * ourShader;
float x_pos = 0.0f;
float y_pos = 0.0f;
float zoom = .01f;
Shader * Mandel;
Camera * test;
Skybox * yo;

void draw_triangle( unsigned int * VAO, int size )
{
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, size / 3);
    glBindVertexArray(0);
}

unsigned int triangle( float * vertices, int size )
{
    unsigned int VAO, VBO;
    
    // Generate VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);
    
    // Specify vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

int display(GLFWwindow* window)
{
    Matrix4 model;
    Matrix4 screen;
    glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS); 
    screen.scale(130);
    screen.translate(0,0,10);
    (*ourShader).use();
    test->Inputs(window);
    test->Matrix(90.0f, 0.001f, 1000.0f, *ourShader, "camMatrix");
    model.rotate(glfwGetTime(), 0.f, 1.f, 0.f);
    ourShader->setMat("model", model.getData().data());
    ratchet->Draw(*ourShader);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        return (42);
    (*Mandel).use();
    test->Matrix(90.0f, 0.001f, 1000.0f, *Mandel, "camMatrix");
    Mandel->setMat("model", screen.getData().data());
    (*Mandel).setFloat("time", glfwGetTime());
    (*Mandel).setFloat("x_pos", x_pos);
    (*Mandel).setFloat("y_pos", y_pos);
    if(zoom < 0.00001f)
        zoom = 0.00001f;
    (*Mandel).setFloat("zoom", zoom);
    (*Mandel).setFloat("resolution", WINDOW_WIDTH, WINDOW_HEIGHT);
    draw_triangle(&triangle1, 9);
    draw_triangle(&triangle2, 9);

    (*ourShader).use();
    (*ourShader).setFloat("time", glfwGetTime());
    (*ourShader).setFloat("resolution", WINDOW_WIDTH, WINDOW_HEIGHT);
    yo->Draw(*test);
    return (0);
}

void create_scene()
{ 
    yo = new Skybox();
    ourShader = new Shader("srcs/ArcticFeather/shaders/vertex.glsl", "srcs/ArcticFeather/shaders/fragment.glsl");
    (*ourShader).use();
    
    Mandel = new Shader("srcs/ArcticFeather/shaders/vertex.glsl", "srcs/ArcticFeather/shaders/n_mandelbrot.glsl");
    (*Mandel).use();

    ratchet = new Model("resources/Ratchet/Ratchet.obj");
    
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


    vec3 camera_pos(0.0f, -1.0f , -5.0f);
    test = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, camera_pos);
}

int main(int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "\033[1;31mERROR::INPUT:: \033[0mExpected only \033[1;32m1\033[0m arguments but got \033[1;31m" << argc - 1 << "\033[0m arguments." << std::endl;
        std::cerr << "\033[1;31mERROR::INPUT:: \033[0mExpected use is \033[1;36m" << argv[0] << " <filename>\033[0m" << std::endl;
        return (1);
    }
    Renderer main_renderer(WINDOW_HEIGHT, WINDOW_WIDTH, "Scop Gtouzali", GL_TRUE, display, GL_FALSE);
    main_renderer.init();
    create_scene(); // replace by scene class
    main_renderer.loop();
    main_renderer.destroy();
}
