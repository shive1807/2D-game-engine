#pragma once
#include "Transform.h"
#include "Shader.h"

namespace Nova{
    class Rectangle{
        public:
        Rectangle();
        ~Rectangle();
        
        Rectangle(const Rectangle&) = delete;
        Rectangle& operator=(const Rectangle&) = delete;

        void Draw() const;

        void SetPosition(float x, float y);
        void SetRotation(float degrees);
        void SetScale(float x, float y);

        private:
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        Shader* m_Shader = nullptr;
        Transform m_Transform;
    };
}