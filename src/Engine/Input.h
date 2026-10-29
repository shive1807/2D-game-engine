#pragma once
#include<GLFW/glfw3.h>

namespace Nova{
    class Input{
        public:
        static void Initialize(GLFWwindow* window);
        static void Update();

        static bool IsKeyPressed(int key);
        static bool IsKeyJustPressed(int key);
        static bool IskeyJustReleased(int key);

        private:
        static GLFWwindow* s_Window;

        static bool s_CurrentKeys[GLFW_KEY_LAST + 1];
        static bool s_PreviousKeys[GLFW_KEY_LAST + 1];
    };
}