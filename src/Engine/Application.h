#pragma once
#include "EngineTime.h"
#include "Camera.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Nova
{
    class Rectangle;

    class Application{
        public:
        Application();
        ~Application();
        void Run();

        private:
        bool Initialize();
        void Update(float deltaTime);
        void Render();
        void Shutdown();

        GLFWwindow* m_window = nullptr;
        bool m_Running = false;

        EngineTime m_Time;

        Rectangle* m_Rectangle = nullptr;

        Camera m_Camera;
    };
}