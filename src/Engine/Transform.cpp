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

    Matrix4 Transform::GetModelMatrix() const{
        Matrix4 translation = Matrix4::Translation(m_PositionX, m_PositionY, 0.0f);
        Matrix4 rotation = Matrix4::RotationZ(m_Rotation);
        Matrix4 scale = Matrix4::Scale(m_ScaleX, m_ScaleY, 1.0f);

        return translation * rotation * scale;
    }
}