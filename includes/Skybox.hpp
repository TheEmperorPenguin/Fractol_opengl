/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-12 14:04:09                                       *
*******************************************************************************/

#ifndef SKYBOX_HPP
    #define SKYBOX_HPP

    #include "ArcticFeather.hpp"

        unsigned int loadCubemap(std::vector<std::string> faces)
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

            int width, height, nrComponents;
            for (unsigned int i = 0; i < faces.size(); i++)
            {
                unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
                if (data)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    stbi_image_free(data);
                }
                else
                {
                    std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                    stbi_image_free(data);
                }
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            return textureID;
        }

    class Skybox
    {
        public:
            Skybox()
            {
                skyboxShader = new Shader("srcs/ArcticFeather/shaders/skybox.vs", "srcs/ArcticFeather/shaders/skybox.fs");
                glGenVertexArrays(1, &skyboxVAO);
                glGenBuffers(1, &skyboxVBO);
                glBindVertexArray(skyboxVAO);
                glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                std::vector<std::string> faces
                {
                    // "resources/textures/skybox/right.jpg",
                    // "resources/textures/skybox/left.jpg",
                    // "resources/textures/skybox/top.jpg",
                    // "resources/textures/skybox/bottom.jpg",
                    // "resources/textures/skybox/front.jpg",
                    // "resources/textures/skybox/back.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                    "resources/textures/skybox/lobozier.jpg",
                };
                cubemapTexture = loadCubemap(faces);
            }
            void Draw(Camera & cam)
            {
                Matrix4 view_sky = cam.v;
                view_sky.setValue(0,3,0);
                view_sky.setValue(0,3,1);
                view_sky.setValue(0,3,2);
                glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
                skyboxShader->use(); // remove translation from the view matrix
                skyboxShader->setMat("view", view_sky.getData().data());
                skyboxShader->setMat("projection", cam.p.getData().data());
                // skybox cube
                glBindVertexArray(skyboxVAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                glBindVertexArray(0);
                glDepthFunc(GL_LESS);
            }
            unsigned int cubemapTexture;
            unsigned int skyboxVAO, skyboxVBO;
            const float skyboxVertices[108] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };
            Shader * skyboxShader;
    };

#endif