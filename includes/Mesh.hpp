/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-09 15:17:14                                       *
*******************************************************************************/

#ifndef MESH_HPP
    #define MESH_HPP

    #include "ArcticFeather.hpp"
    #include <array>


    struct Vertex
    {
        std::array<float, 3> Position;
        std::array<float, 3> Normal;
        std::array<float, 2> TexCoords;
    };

    struct Texture
    {
        unsigned int id;
        std::string type;
    };
    
    class Mesh
    {
        public:
            // mesh data
            std::vector<Vertex>       vertices;
            std::vector<unsigned int> indices;
            std::vector<Texture>      textures;
            unsigned int VAO;

            Mesh( std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures )
            {
                this->vertices  = vertices;
                this->indices   = indices;
                this->textures  = textures;

                setupMesh();
            }
            
            void Draw(Shader &shader)
            {
                shader.use();
                // unsigned int diffuseNr  = 1;
                // unsigned int specularNr = 1;
                // unsigned int normalNr   = 1;
                // unsigned int heightNr   = 1;
                // for(unsigned int i = 0; i < textures.size(); i++)
                // {
                //     glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                //     // retrieve texture number (the N in diffuse_textureN)
                //     std::string number;
                //     std::string name = textures[i].type;
                //     if(name == "texture_diffuse")
                //         number = std::to_string(diffuseNr++);
                //     else if(name == "texture_specular")
                //         number = std::to_string(specularNr++);
                //     else if(name == "texture_normal")
                //         number = std::to_string(normalNr++);
                //     else if(name == "texture_height")
                //         number = std::to_string(heightNr++);

                //     // now set the sampler to the correct texture unit
                //     glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
                //     // and finally bind the texture
                //     glBindTexture(GL_TEXTURE_2D, textures[i].id);
                // }
                
                // draw mesh
                glBindVertexArray(VAO);
                glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);

                // always good practice to set everything back to defaults once configured.
                // glActiveTexture(GL_TEXTURE0);
            }
        private:
            //  render data
            unsigned int VBO, EBO;

            void setupMesh()
            {
                // create buffers/arrays
                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);
                glGenBuffers(1, &EBO);

                glBindVertexArray(VAO);
                // load data into vertex buffers
                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

                // set the vertex attribute pointers
                // vertex Positions
                glEnableVertexAttribArray(0);	
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
                // vertex normals
                glEnableVertexAttribArray(1);	
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
                // vertex texture coords
                glEnableVertexAttribArray(2);	
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

                glBindVertexArray(0);
            }
    };  
#endif