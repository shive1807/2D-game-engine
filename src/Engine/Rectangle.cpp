#include "Rectangle.h"
#include <glad/gl.h>
#include <iostream>

namespace Nova{
    Rectangle::Rectangle(){
        const char* vertexSource = R"(#version 330 core
            layout (location = 0) in vec2 a_Position;
            void main()
            {
                gl_Position = vec4(a_Position, 0.0, 1.0);
            }
        )";

        const char* fragmentSource = R"(#version 330 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(0.2, 0.7, 1.0, 1.0);
            }
        )";

        m_Shader = new Shader(vertexSource, fragmentSource);

        const float vertices[] = 
        {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,

            -0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Rectangle::~Rectangle(){
        delete m_Shader;

        if(m_VBO != 0){
            glDeleteBuffers(1, &m_VBO);
        }
        if(m_VAO != 0){
            glDeleteVertexArrays(1, &m_VAO);
        }
    }

    void Rectangle::Draw() const{
        m_Shader->Bind();

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        m_Shader->UnBind();
    }
}