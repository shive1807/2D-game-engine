#include "Transform.h"
namespace Nova{
    
    void Transform::SetPosition(float x, float y){
        m_PositionX = x;
        m_PositionY = y;
    }

    void Transform::SetRotation(float degrees){
        m_Rotation = degrees;
    }

    void Transform::SetScale(float x, float y){
        m_ScaleX = x;
        m_ScaleY = y;
    }

    float Transform::GetPositionX() const{
        return m_PositionX;
    }

    float Transform::GetPositionY() const{
        return m_PositionY;
    }

    float Transform::GetRotation() const{
        return m_Rotation;
    }

    float Transform::GetScaleX() const{
        return m_ScaleX;
    }

    float Transform::GetScaleY() const{
        return m_ScaleY;
    }
}