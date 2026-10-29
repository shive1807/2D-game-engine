#include<Application.h>
#include<iostream>

namespace Nova{
    Application::Application() = default;

    Application::~Application(){
        Shutdown();
    }

    bool Application::Initialize(){
        if(!glfwInit()){
            std::cerr <<"Failed to initialize GLFW\n";
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        m_window = glfwCreateWindow(1280, 720, "Nova2D - Application", nullptr, nullptr);

        if(m_window == nullptr){
            std::cerr << "Failed to create window\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1);

        m_Running = true;

        std::cout << "Nova2D initialized successfully!\n";
        return true;
    }

    void Application::Run(){
        if(!Initialize()){
            return;
        }

        m_Time.Reset();

        while(m_Running && !glfwWindowShouldClose(m_window)){
            glfwPollEvents();
            m_Time.Tick();
            const float deltaTime = m_Time.GetDeltaTime();
            Update(deltaTime);
            Render();
            glfwSwapBuffers(m_window);
        }
    }

    void Application::Update(float deltaTime){
        static float printTimer = 0.0f;

        printTimer += deltaTime;

        if (printTimer >= 1.0f)
        {
            std::cout
                << "Elapsed: " << m_Time.GetElapsedTime()
                << " s | Delta: " << deltaTime
                << " s | FPS: " << 1.0f / deltaTime
                << '\n';

            printTimer = 0.0f;
        }
        //game logic will go here
    }

    void Application::Render(){
        glClearColor(0.10f, 0.12f, 0.16f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Application::Shutdown(){
        if(m_window != nullptr){
            glfwDestroyWindow(m_window);
            m_window = nullptr;
            glfwTerminate();
        }

        m_Running = false;
    }
}