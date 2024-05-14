/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-12 11:59:30                                       *
*******************************************************************************/

#ifndef ARCTICFEATHER_HPP
    #define ARCTICFEATHER_HPP
    
    #ifndef TESTING
        #include "imgui.h"
        #include "imgui_impl_glfw.h"
        #include "imgui_impl_opengl3.h"

        #include "./include/glad/glad.h"
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
    #endif

    #ifdef TESTING
        #include "colorful_code.hpp"
    #endif

    #include <cstdio>
    #include <vector>
    #include <iostream>
    #include <iomanip>
    #include <fstream>
    #include <sstream>
    #include <string>

    #ifndef TESTING
        #define STB_IMAGE_IMPLEMENTATION
        #include "stb_image.h"
        #include "Renderer.hpp"
        #include "Shader.hpp"
        #include "Matrix.hpp"
        #include "Matrix4x4.hpp"
        #include "Vec3.hpp"
        #include "Camera.hpp"
        #include "Mesh.hpp"
        #include "Model.hpp"
        #include "Skybox.hpp"
    #endif

#endif
