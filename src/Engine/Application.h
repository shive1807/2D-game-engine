#pragma once

#include <GLFW/glfw3.h>

namespace Nova
{
    class Application{
        public:
        Application();
        ~Application();
        void Run();

        private:
        bool Initialize();
        void Update();
        void Render();
        void Shutdown();

        GLFWwindow* m_window = nullptr;
        bool m_Running = false;
    };
}