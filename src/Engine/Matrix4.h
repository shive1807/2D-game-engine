#pragma once

namespace Nova {

    class Matrix4 {
    public:
        Matrix4();
        explicit Matrix4(float diagonal);

        float& operator()(int row, int column);
        float operator()(int row, int column) const;

        const float* Data() const;

        static Matrix4 Identity();

        Matrix4 operator*(const Matrix4& other) const;

        static Matrix4 Translation(float x, float y, float z);
        static Matrix4 RotationZ(float degrees);
        static Matrix4 Scale(float x, float y, float z);

        static Matrix4 Orthographic(
            float left, 
            float right, 
            float bottom, 
            float top, 
            float nearPlane,
            float farPlane
        );
        
    private:
        float m_Data[16];
    };
}