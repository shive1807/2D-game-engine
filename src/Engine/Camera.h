#pragma once
namespace Nova{
    class Camera{
        public:
        Camera(float viewWidth = 16.0f, float viewHeight = 9.0f);

        void SetPosition(float x, float y);
        void SetViewSize(float width, float height);

        float GetPositionX() const;
        float GetPositionY() const;
        float GetViewWidth() const;
        float GetViewHeight() const;

        private:
        float m_PositionX = 0.0f;
        float m_PositionY = 0.0f;

        float m_ViewWidth;
        float m_ViewHeight;
    };
}