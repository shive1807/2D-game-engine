#include "Rectangle.h"
#include "Camera.h"
#include "Matrix4.h"
#include <glad/gl.h>
#include <iostream>

namespace Nova {

    Rectangle::Rectangle() {
        const char* vertexSource = R"(#version 330 core
            layout (location = 0) in vec2 a_Position;

            uniform mat4 u_MVP;

            void main()
            {
                vec4 position = vec4(a_Position, 0.0, 1.0);
                gl_Position = u_MVP * position;
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

        const float vertices[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,

            -0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            2 * sizeof(float),
            nullptr
        );

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Rectangle::~Rectangle() {
        delete m_Shader;
        m_Shader = nullptr;

        if (m_VBO != 0) {
            glDeleteBuffers(1, &m_VBO);
            m_VBO = 0;
        }

        if (m_VAO != 0) {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }
    }

    void Rectangle::Draw(const Camera& camera) const {
        m_Shader->Bind();

        const Matrix4 model = m_Transform.GetModelMatrix();
        const Matrix4 view = camera.GetViewMatrix();
        const Matrix4 projection = camera.GetProjectionMatrix();
        const Matrix4 mvp = projection * view * model;

        const GLint program = static_cast<GLint>(m_Shader->GetRendererID());
        const GLint mvpLocation = glGetUniformLocation(program, "u_MVP");
        glUniformMatrix4fv(
            mvpLocation,
            1,
            GL_FALSE,
            mvp.Data()
        );

        // Draw the rectangle.
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        m_Shader->UnBind();
    }

    void Rectangle::SetPosition(float x, float y) {
        m_Transform.SetPosition(x, y);
    }

    void Rectangle::SetRotation(float degrees) {
        m_Transform.SetRotation(degrees);
    }

    void Rectangle::SetScale(float x, float y) {
        m_Transform.SetScale(x, y);
    }
}