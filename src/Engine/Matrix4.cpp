#include "Matrix4.h"

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

}