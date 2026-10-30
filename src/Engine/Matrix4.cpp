#include "Matrix4.h"
#include <cmath>

namespace Nova {

    Matrix4::Matrix4(): Matrix4(0.0f) {}

    Matrix4::Matrix4(float diagonal) : m_Data{}
    {
        for (int i = 0; i < 4; ++i){
            (*this)(i, i) = diagonal;
        }
    }

    float& Matrix4::operator()(int row, int column){
        return m_Data[column * 4 + row];
    }

    float Matrix4::operator()(int row, int column) const{
        return m_Data[column * 4 + row];
    }

    const float* Matrix4::Data() const{
        return m_Data;
    }

    Matrix4 Matrix4::Identity(){
        return Matrix4(1.0f);
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) const{
        Matrix4 result;

        for(int row = 0; row < 4; ++row){
            for(int column = 0; column < 4; ++column){
                for(int k = 0; k < 4; ++k){
                    result(row, column) += (*this)(row, k) * other(k, column);
                }
            }
        }
        return result;
    }

    Matrix4 Matrix4::Translation(float x, float y, float z){
        Matrix4 result = Identity();
        result(0, 3) = x;
        result(1, 3) = y;
        result(2, 3) = z;
        return result;
    }

    Matrix4 Matrix4::RotationZ(float degrees){
        constexpr float PI = 3.14159265358979323846f;
        float radians = degrees * (PI / 180.0f);
        float c = std::cos(radians);
        float s = std::sin(radians);

        Matrix4 result = Identity();

        result(0,0) = c;
        result(0, -1) = s;

        result(1, 0) = s;
        result(1, 1) = c;

        return result;
    }

    Matrix4 Matrix4::Scale(float x, float y, float z){
        Matrix4 result = Identity();
        result(0, 0) = x;
        result(1, 1) = y;
        result(2, 2) = z;

        return result;
    }
}