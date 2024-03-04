/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-29 14:26:52                                       *
*******************************************************************************/

#include "ArcticFeather.hpp"

GLFWwindow* window;

void error_callback( int error, const char* description )
{
   std::cerr << "Error " << error << ":" << description << std::endl;
}

void framebuffer_size_callback( GLFWwindow* window, int width, int height )
{
    glViewport(0, 0, width, height);
    (void)window;
}

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


int AF_init(int             window_width,
            int             window_height,
            const char *    window_title,
            void (*scene_init)(void),
            void (*display)(GLFWwindow*),
            void (*keypress)(GLFWwindow* , int, int, int, int)
            )
{

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);
    window = glfwCreateWindow(window_height, window_width, window_title, NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return (2);
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(); 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(0); //vsync if 1
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    if (scene_init)
        scene_init();
    if (keypress)
        glfwSetKeyCallback(window, (GLFWkeyfun)keypress);
    int frameCount = 0;
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - prevTime;
        frameCount++;
        if (deltaTime >= 1.0) {
            double fps = frameCount / deltaTime;
            std::string windowTitle = window_title;
            windowTitle +=  " | FPS: " + std::to_string(static_cast<int>(fps));
            glfwSetWindowTitle(window, windowTitle.c_str());

            // Reset frame count and time
            frameCount = 0;
            prevTime = currentTime;
        }
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();


        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (display)
            display(window);
        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}

int AF_destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(); 
    glfwDestroyWindow(window);
    glfwTerminate();
    return (0);
}
