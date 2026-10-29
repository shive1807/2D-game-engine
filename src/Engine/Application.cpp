#include<Application.h>
#include "Input.h"
#include "Renderer.h"
#include "Rectangle.h"
#include <glad/gl.h>
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

        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD!" << std::endl;
            return false;
        }
        m_Rectangle = new Rectangle();
        m_Rectangle->SetPosition(0.5f, 0.0f);
        
        glfwSwapInterval(1);

        m_Running = true;

        //Input system
        Input::Initialize(m_window);

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
            
            Input::Update();
            
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

    // void Application::Render(){
    //     Renderer::Clear(0.10f, 0.10f, 0.15f, 1.0f);
    //     if (m_Rectangle != nullptr){
    //         m_Rectangle->Draw();
    //     }
    // }

    void Application::Render()
    {
        Renderer::Clear(0.10f, 0.10f, 0.15f, 1.0f);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_Rectangle != nullptr)
        {
            m_Rectangle->Draw();
        }
    }

    void Application::Shutdown(){
        if(m_window != nullptr){
            delete m_Rectangle;
            m_Rectangle = nullptr;
            glfwDestroyWindow(m_window);
            m_window = nullptr;
            glfwTerminate();
        }

        m_Running = false;
    }
}