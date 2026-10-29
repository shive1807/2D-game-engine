#include "Shader.h"

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>

#include <iostream>

namespace Nova{
    Shader::Shader(const char* vertexSource, const char* fragmentSource){
        //Create the vertex shader
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);

        int success = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if(!success){
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Vertex shader compilation failded:\n" << infoLog << "\n";
        }

        //Create a fragment shader
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if(!success){
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
            std::cerr<< "Fragment shader compilation failed: \n" << infoLog << '\n';
        }

        //Link both shader into one shader program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);

        if(!success){
            char infoLog[512];
            glGetProgramInfoLog(m_RendererID, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Shader program linking failed:\n" << infoLog << '\n';
        }

        // The program now contains the linked shader code
        // Individual shader objects can be deleted 
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader(){
        if(m_RendererID != 0){
            glDeleteProgram(m_RendererID);
        }
    }

    void Shader::Bind() const{
        glUseProgram(m_RendererID);
    }

    void Shader::UnBind() const{
        glUseProgram(0);
    }
}