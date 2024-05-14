/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-12 13:01:00                                       *
*******************************************************************************/

#ifndef MODEL_HPP
    #define MODEL_HPP

    #include "ArcticFeather.hpp"

    class Model 
    {
        public:
            Model(std::string path)
            {
                loadModel(path.c_str());
            }
            void Draw(Shader &shader)
            {
                shader.use();
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, vertices.size());
                glBindVertexArray(0);
            }	
        private:
            // model data
            std::vector<Mesh> meshes;
            std::string directory;
            std::vector < std::array<float, 3> > vertices;
            std::vector < std::array<float, 2> > uvs;
            std::vector < std::array<float, 3> > normals;
            GLuint vao;
            GLuint vbo;
            GLuint uvVbo;
            GLuint normalVbo;

            void loadModel( const char * path )
            {
                std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
                std::vector< std::array<float, 3> > temp_vertices;
                std::vector< std::array<float, 2> > temp_uvs;
                std::vector< std::array<float, 3> > temp_normals;

                std::cout << path << std::endl;
                FILE * file = fopen( path, "r" );
                if( file == NULL ){
                    std::cout << "Error while opening file" << std::endl;
                    return ;
                }
                while (42)
                {
                    char lineHeader[256];
                    int res = fscanf(file, "%s", lineHeader);
                    if ( res == EOF )
                        break;
                    if ( strcmp( lineHeader, "v" ) == 0 )
                    {
                        std::array<float, 3> vertex;
                        fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2] );
                        temp_vertices.push_back(vertex);
                    }
                    else if ( strcmp( lineHeader, "vt" ) == 0 )
                    {
                        std::array<float, 2> uv;
                        fscanf(file, "%f %f\n", &uv[0], &uv[1] );
                        temp_uvs.push_back(uv);
                    }
                    else if ( strcmp( lineHeader, "vn" ) == 0 )
                    {
                        std::array<float, 3> normal;
                        fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
                        temp_normals.push_back(normal);
                    }
                    else if ( strcmp( lineHeader, "f" ) == 0 )
                    {
                        std::string vertex1, vertex2, vertex3;
                        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                        if (matches != 9){
                            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                            return ;
                        }
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                        uvIndices    .push_back(uvIndex[0]);
                        uvIndices    .push_back(uvIndex[1]);
                        uvIndices    .push_back(uvIndex[2]);
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                    }
                    else
                    {
                        char stupidBuffer[1000];
                        fgets(stupidBuffer, 1000, file);
                    }
                }

                for( unsigned int i=0; i<vertexIndices.size(); i++ ){
                    unsigned int vertexIndex = vertexIndices[i];
                    unsigned int uvIndex = uvIndices[i];
                    unsigned int normalIndex = normalIndices[i];
                    
                    std::array<float, 3> vertex = temp_vertices[ vertexIndex-1 ];
                    std::array<float, 2> uv = temp_uvs[ uvIndex-1 ];
                    std::array<float, 3> normal = temp_normals[ normalIndex-1 ];
                    
                    vertices.push_back(vertex);
                    uvs     .push_back(uv);
                    normals .push_back(normal);
                }


                    glGenVertexArrays(1, &vao);
                    glBindVertexArray(vao);

                    // Create VBO for vertices
                    glGenBuffers(1, &vbo);
                    glBindBuffer(GL_ARRAY_BUFFER, vbo);
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(std::array<float, 3>), vertices.data(), GL_STATIC_DRAW);
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(0);

                    // Create VBO for UVs
                    glGenBuffers(1, &uvVbo);
                    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
                    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(std::array<float, 2>), uvs.data(), GL_STATIC_DRAW);
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(1);

                    // Create VBO for normals
                    glGenBuffers(1, &normalVbo);
                    glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
                    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::array<float, 3>), normals.data(), GL_STATIC_DRAW);
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                    glEnableVertexAttribArray(2);

                return ;
            }
    };

#endif