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

    private:
        float m_Data[16];
    };

}