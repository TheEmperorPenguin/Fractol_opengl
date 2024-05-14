/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-12 11:23:57                                       *
*******************************************************************************/

#ifndef RENDERER_HPP
    #define RENDERER_HPP

#include "ArcticFeather.hpp"

void error_callback( int error, const char* description );

class Renderer
{
    public:
        Renderer(GLuint width, GLuint height, const char * title, GLboolean vsync, int (*display)(GLFWwindow*), GLboolean fullscreen)
        {
            this->vsync = vsync;
            this->width = width;
            this->height = height;
            this->title = title;
            this->display = display;
            this->fullscreen = fullscreen;
        }
        int init()
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
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwSetErrorCallback(error_callback);
            if (fullscreen == GL_TRUE)
            {
                this->width = 1920;
                this->height = 1080;
                window = glfwCreateWindow(this->height, this->width, this->title, glfwGetPrimaryMonitor(), NULL);
            }
            else
                window = glfwCreateWindow(this->height, this->width, this->title, NULL, NULL);
            if (!window)
            {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return (2);
            }
            glfwMakeContextCurrent(window);
            gladLoadGL(); 
            // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSwapInterval(this->vsync); //vsync if 1
            glEnable(GL_MULTISAMPLE);
            return 0;
        }
        
        int loop()
        {
            int frameCount = 0;
            double prevTime = glfwGetTime();
            double last_frame = prevTime;
            double fps = 0;
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS); 
            while (!glfwWindowShouldClose(window))
            {
                double currentTime = glfwGetTime();

                double deltaTime = currentTime - prevTime;
                std::string windowTitle = this->title;
                frameCount++;
                if (deltaTime >= 1.0) {
                    fps = frameCount / deltaTime;

                    // Reset frame count and time
                    frameCount = 0;
                    prevTime = currentTime;
                }
                windowTitle +=  " | FPS: " + std::to_string(static_cast<int>(fps)) + " " + std::to_string(currentTime - last_frame) + "ms";
                last_frame = glfwGetTime();
                glfwSetWindowTitle(window, windowTitle.c_str());
                glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glfwPollEvents();

                int display_exit_code = 0;
                if (this->display)
                    display_exit_code = this->display(window);
                if (display_exit_code == 42)
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    

                int display_w, display_h;
                glfwGetFramebufferSize(window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);

                glfwPollEvents();
                glfwSwapBuffers(window);
            }
            return(0);
        }
        int destroy()
        {

            glfwDestroyWindow(window);
            glfwTerminate();
            return (0);
        }
    private:
        GLboolean       vsync;
        GLboolean       fullscreen;
        int            (*display)(GLFWwindow*);
        GLFWwindow*     window;
        GLuint          width ;
        GLuint          height;
        const char *    title ;
};

void error_callback( int error, const char* description )
{
    std::cerr << "Error " << error << ":" << description << std::endl;
}

#endif