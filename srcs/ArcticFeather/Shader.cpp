/*******************************************************************************
* @author:    Gabriel Touzalin                          ▄███▀▄     ▄▀███▄      *
* @contact:   gabriel.touzalin@gmail.com                ██████▀▀ ▀▀██████      *
* @github:    https://github.com/TheEmperorPenguin     ████ █  ▄▄▄ █ ████      *
* @date:      1970-01-01 01:00:00                      ██▀█ █ █▄▀▄█ █ █▀██     *
*                                                     ▀▀█▄▄█▀ ▀███▀ ▀█▄▄█▀▀    *
* @lastModifiedBy:   Gabriel TOUZALIN                                          *
* @lastModifiedTime: 2024-02-28 17:36:04                                       *
*******************************************************************************/

#include "./Shader.hpp"

Shader::Shader( const char* vertexPath, const char* fragmentPath )
{
    std::string     vertexCode;
    std::string     fragmentCode;
    std::ifstream   vertexFile;
    std::ifstream   fragmentFile;

    vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vertexFile.rdbuf();
        fShaderStream << fragmentFile.rdbuf();	
        vertexFile.close();
        fragmentFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch( const std::exception& e )
    {
        std::cerr << "SHADER::" << e.what() << std::endl;
    }
    
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(this->ID);
}
            
void Shader::setBool( const std::string &name, bool value ) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt( const std::string &name, int value ) const
{
     glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt( const std::string &name, int x, int y ) const
{
    glUniform2i(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void Shader::setInt( const std::string &name, int x, int y, int z ) const
{
    glUniform3i(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setInt( const std::string &name, int x, int y, int z, int w ) const
{
    glUniform4i(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

void Shader::setFloat( const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat( const std::string &name, float x, float y ) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}

void Shader::setFloat( const std::string &name, float x, float y, float z ) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void Shader::setFloat( const std::string &name, float x, float y, float z, float w ) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}
