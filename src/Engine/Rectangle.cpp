#include "Rectangle.h"
#include "Camera.h"
#include <glad/gl.h>

namespace Nova {

    Rectangle::Rectangle() {
        const char* vertexSource = R"(#version 330 core
            layout (location = 0) in vec2 a_Position;

            uniform vec2 u_Position;
            uniform float u_Rotation;
            uniform vec2 u_Scale;

            uniform vec2 u_CameraPosition;
            uniform vec2 u_ViewSize;

            void main()
            {
                // Apply object scale.
                vec2 scaledPosition = a_Position * u_Scale;

                // Apply object rotation.
                float c = cos(radians(u_Rotation));
                float s = sin(radians(u_Rotation));

                mat2 rotation = mat2(
                    c, s,
                    -s, c
                );

                vec2 rotatedPosition = rotation * scaledPosition;

                // Convert local position to world position.
                vec2 worldPosition = rotatedPosition + u_Position;

                // Convert world position to camera-relative position.
                vec2 cameraPosition = worldPosition - u_CameraPosition;

                // Convert camera-relative coordinates to clip space.
                vec2 clipPosition = cameraPosition * (2.0 / u_ViewSize);

                gl_Position = vec4(clipPosition, 0.0, 1.0);
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

        const GLint program =
            static_cast<GLint>(m_Shader->GetRendererID());

        // Object transform uniforms.
        const GLint positionLocation =
            glGetUniformLocation(program, "u_Position");

        const GLint rotationLocation =
            glGetUniformLocation(program, "u_Rotation");

        const GLint scaleLocation =
            glGetUniformLocation(program, "u_Scale");

        glUniform2f(
            positionLocation,
            m_Transform.GetPositionX(),
            m_Transform.GetPositionY()
        );

        glUniform1f(
            rotationLocation,
            m_Transform.GetRotation()
        );

        glUniform2f(
            scaleLocation,
            m_Transform.GetScaleX(),
            m_Transform.GetScaleY()
        );

        // Camera uniforms.
        const GLint cameraPositionLocation =
            glGetUniformLocation(program, "u_CameraPosition");

        const GLint viewSizeLocation =
            glGetUniformLocation(program, "u_ViewSize");

        glUniform2f(
            cameraPositionLocation,
            camera.GetPositionX(),
            camera.GetPositionY()
        );

        glUniform2f(
            viewSizeLocation,
            camera.GetViewWidth(),
            camera.GetViewHeight()
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