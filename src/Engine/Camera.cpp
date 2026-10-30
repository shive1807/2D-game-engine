#include "Camera.h"

namespace Nova {

    Camera::Camera(float viewWidth, float viewHeight)
        : m_ViewWidth(viewWidth),
          m_ViewHeight(viewHeight)
    {
    }

    void Camera::SetPosition(float x, float y)
    {
        m_PositionX = x;
        m_PositionY = y;
    }

    void Camera::SetViewSize(float width, float height)
    {
        if (width <= 0.0f || height <= 0.0f)
        {
            return;
        }

        m_ViewWidth = width;
        m_ViewHeight = height;
    }

    float Camera::GetPositionX() const
    {
        return m_PositionX;
    }

    float Camera::GetPositionY() const
    {
        return m_PositionY;
    }

    float Camera::GetViewWidth() const
    {
        return m_ViewWidth;
    }

    float Camera::GetViewHeight() const
    {
        return m_ViewHeight;
    }

}