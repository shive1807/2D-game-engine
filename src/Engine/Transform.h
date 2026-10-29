#pragma once

namespace Nova{
    class Transform{
        public:
        Transform() = default;

        void SetPosition(float x, float y);
        void SetRotation(float degrees);
        void SetScale(float x, float y);

        float GetPositionX() const;
        float GetPositionY() const;
        float GetRotation() const;
        float GetScaleX() const;
        float GetScaleY() const;

        private:
        float m_PositionX = 0.0f;
        float m_PositionY = 0.0f;
        float m_Rotation = 0.0f;
        float m_ScaleX = 1.0f;
        float m_ScaleY = 1.0f;
    };
}