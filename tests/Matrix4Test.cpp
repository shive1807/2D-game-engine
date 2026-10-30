#include "Matrix4.h"
#include <iostream>

int main()
{
    Nova::Matrix4 projection = Nova::Matrix4::Orthographic(
        -8.0f,
         8.0f,
        -4.5f,
         4.5f,
        -1.0f,
         1.0f
    );

    std::cout << "Orthographic Projection Matrix:\n";

    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            std::cout << projection(row, column) << "\t";
        }

        std::cout << '\n';
    }

    return 0;
}