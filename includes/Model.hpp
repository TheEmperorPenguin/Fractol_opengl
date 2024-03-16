/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-03-06 10:49:11                                       *
*******************************************************************************/

#ifndef MODEL_HPP
    #define MODEL_HPP

    #include "ArcticFeather.hpp"

    class Model 
    {
        public:
            Model(char *path)
            {
                loadModel(path);
            }
            void Draw(Shader &shader);	
        private:
            // model data
            std::vector<Mesh> meshes;
            std::string directory;

            void loadModel(std::string path);


            // void processNode(aiNode *node, const aiScene *scene);
            // Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            // vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
            //                                     string typeName);
    };

#endif