/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-28 17:37:23                                       *
*******************************************************************************/

#ifndef SHADER_HPP
    #define SHADER_HPP

    #include "ArcticFeather.hpp"

    class Shader
    {
        public:

            unsigned int ID;
        
            Shader( const char* vertexPath, const char* fragmentPath );

            void use();
            
            void setBool( const std::string &name, bool value ) const;  

            void setInt( const std::string &name, int value ) const;
            void setInt( const std::string &name, int x, int y ) const;
            void setInt( const std::string &name, int x, int y, int z ) const;
            void setInt( const std::string &name, int x, int y, int z, int w ) const;

            void setFloat( const std::string &name, float value ) const;
            void setFloat( const std::string &name, float x, float y ) const;
            void setFloat( const std::string &name, float x, float y, float z ) const;
            void setFloat( const std::string &name, float x, float y, float z, float w ) const;
    };

#endif