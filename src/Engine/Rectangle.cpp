#include "Rectangle.h"
#include <glad/gl.h>
#include <iostream>

namespace Nova{
    Rectangle::Rectangle(){
        const char* vertexSource = R"(#version 330 core
            layout (location = 0) in vec2 a_Position;
            
            uniform vec2 u_Position;
            uniform float u_Rotation;
            uniform vec2 u_Scale;

            void main()
            {

                vec2 scaledPosition = a_Position * u_Scale;

                float c = cos(radians(u_Rotation));
                float s = sin(radians(u_Rotation));

                mat2 rotation = mat2(
                    c, s,
                    -s, c
                );
                vec2 rotatedPosition = rotation * scaledPosition;
            
                gl_Position = vec4(rotatedPosition + u_Position, 0.0, 1.0);
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
        GLint program = static_cast<GLint>(m_Shader->GetRendererID());

        GLint positionLocation = glGetUniformLocation(program, "u_Position");
        GLint rotationLocation = glGetUniformLocation(program, "u_Rotation");
        GLint scaleLocation = glGetUniformLocation(program, "u_Scale");

        glUniform2f(positionLocation, m_Transform.GetPositionX(), m_Transform.GetPositionY());
        glUniform1f(rotationLocation, m_Transform.GetRotation());
        glUniform2f(scaleLocation, m_Transform.GetScaleX(), m_Transform.GetScaleY());

        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        m_Shader->UnBind();
    }

    void Rectangle::SetPosition(float x, float y){
        m_Transform.SetPosition(x, y);
    }

    void Rectangle::SetRotation(float degrees)
    {
        m_Transform.SetRotation(degrees);
    }

    void Rectangle::SetScale(float x, float y)
    {
        m_Transform.SetScale(x, y);
    }
}