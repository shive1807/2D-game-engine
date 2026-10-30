
#include "Matrix4.h"
#include "Transform.h"
#include "Camera.h"

#include <cmath>
#include <iostream>

namespace
{
    constexpr float EPSILON = 0.0001f;

    int failedTests = 0;
    int passedTests = 0;

    bool NearlyEqual(float actual, float expected)
    {
        return std::abs(actual - expected) <= EPSILON;
    }

    void AssertMatrix(
        const Nova::Matrix4& actual,
        const Nova::Matrix4& expected,
        const char* testName
    )
    {
        bool passed = true;

        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                const float actualValue = actual(row, column);
                const float expectedValue = expected(row, column);

                if (!NearlyEqual(actualValue, expectedValue))
                {
                    passed = false;

                    std::cout
                        << "  Mismatch at [" << row << "][" << column << "]"
                        << " | Expected: " << expectedValue
                        << " | Actual: " << actualValue
                        << '\n';
                }
            }
        }

        if (passed)
        {
            ++passedTests;
            std::cout << "[PASS] " << testName << '\n';
        }
        else
        {
            ++failedTests;
            std::cout << "[FAIL] " << testName << '\n';
        }
    }

    void TestOrthographicMatrix()
    {
        const Nova::Matrix4 projection = Nova::Matrix4::Orthographic(
            -8.0f, 8.0f,
            -4.5f, 4.5f,
            -1.0f, 1.0f
        );

        Nova::Matrix4 expected = Nova::Matrix4::Identity();

        expected(0, 0) = 0.125f;
        expected(1, 1) = 2.0f / 9.0f;
        expected(2, 2) = -1.0f;

        AssertMatrix(
            projection,
            expected,
            "Orthographic Projection Matrix"
        );
    }

    void TestModelMatrix()
    {
        Nova::Transform transform;

        transform.SetPosition(3.0f, 2.0f);
        transform.SetRotation(90.0f);
        transform.SetScale(2.0f, 2.0f);

        const Nova::Matrix4 model = transform.GetModelMatrix();

        Nova::Matrix4 expected = Nova::Matrix4::Identity();

        expected(0, 0) = 0.0f;
        expected(0, 1) = -2.0f;
        expected(0, 3) = 3.0f;

        expected(1, 0) = 2.0f;
        expected(1, 1) = 0.0f;
        expected(1, 3) = 2.0f;

        AssertMatrix(
            model,
            expected,
            "Model Matrix"
        );
    }

    void TestCameraViewMatrix()
    {
        Nova::Camera camera;

        camera.SetPosition(5.0f, 3.0f);

        const Nova::Matrix4 view = camera.GetViewMatrix();

        Nova::Matrix4 expected = Nova::Matrix4::Identity();

        expected(0, 3) = -5.0f;
        expected(1, 3) = -3.0f;

        AssertMatrix(
            view,
            expected,
            "Camera View Matrix"
        );
    }
}

void TestCameraProjectionMatrix()
{
    Nova::Camera camera(16.0f, 9.0f);

    const Nova::Matrix4 projection = camera.GetProjectionMatrix();

    const Nova::Matrix4 expected = Nova::Matrix4::Orthographic(
        -8.0f, 8.0f,
        -4.5f, 4.5f,
        -1.0f, 1.0f
    );

    AssertMatrix(
        projection,
        expected,
        "Camera Projection Matrix"
    );
}

void TestMVPMatrix()
{
    Nova::Transform transform;
    transform.SetPosition(3.0f, 2.0f);

    Nova::Camera camera(16.0f, 9.0f);
    camera.SetPosition(5.0f, 3.0f);

    const Nova::Matrix4 model = transform.GetModelMatrix();
    const Nova::Matrix4 view = camera.GetViewMatrix();
    const Nova::Matrix4 projection = camera.GetProjectionMatrix();

    const Nova::Matrix4 mvp = projection * view * model;

    Nova::Matrix4 expected = Nova::Matrix4::Identity();

    expected(0, 0) = 0.125f;
    expected(1, 1) = 2.0f / 9.0f;
    expected(2, 2) = -1.0f;

    expected(0, 3) = -0.25f;
    expected(1, 3) = -2.0f / 9.0f;

    AssertMatrix(mvp, expected, "MVP Matrix");
}

int main()
{
    std::cout << "\n========== Nova2D Math Tests ==========\n\n";

    TestOrthographicMatrix();
    TestModelMatrix();
    TestCameraViewMatrix();
    TestCameraProjectionMatrix();
    TestMVPMatrix();

    std::cout << "\n=======================================\n";
    std::cout << "Tests passed: " << passedTests << '\n';
    std::cout << "Tests failed: " << failedTests << '\n';
    std::cout << "=======================================\n";

    if (failedTests > 0)
    {
        std::cout << "Some tests failed!\n";
        return 1;
    }

    std::cout << "All tests passed!\n";
    return 0;
}
