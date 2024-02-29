/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-29 14:06:54                                       *
*******************************************************************************/

#ifndef ARCTICFEATHER_HPP
    #define ARCTICFEATHER_HPP
    
    #include "imgui.h"
    #include "imgui_impl_glfw.h"
    #include "imgui_impl_opengl3.h"

    #include "./include/glad/glad.h"
    #include "./glm/glm.hpp"
    #ifdef __APPLE__
        #define	GL_SILENCE_DEPRECATION
        # define __gl_h_
        # define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
        #include <GLFW/glfw3.h>
        #include <OpenGL/gl3.h>
        #include <OpenGL/gl3ext.h>  
    #else
        #include <math.h>

        #define GL_GLEXT_PROTOTYPES
        #include <GLFW/glfw3.h>
    #endif

    #include <cstdio>
    #include <vector>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>

    #include "./Shader.hpp"

int AF_init(int             window_width,
            int             window_height,
            const char *    window_title,
            void (scene_init)(void),
            void (display)( GLFWwindow* window ),
            void (*keypress)( GLFWwindow* window, int key, int scancode, int action, int mods )
            );
int AF_destroy(void);

int ObjLoader( char * path, std::vector < glm::vec3 > & output );

unsigned int triangle( float * vertices, int size );

void draw_triangle( unsigned int * VAO, int size );

#endif
