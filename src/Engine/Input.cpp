#include "Input.h"

namespace Nova{
    GLFWwindow* Input::s_Window = nullptr;

    bool Input::s_CurrentKeys[GLFW_KEY_LAST + 1] = {};
    bool Input::s_PreviousKeys[GLFW_KEY_LAST + 1] = {};

    void Input::Initialize(GLFWwindow* window){
        s_Window = window;
    }

    void Input::Update(){
        if(s_Window == nullptr){
            return;
        }

        for(int key = 0; key <= GLFW_KEY_LAST; ++key){
            s_PreviousKeys[key] = s_CurrentKeys[key];
            s_CurrentKeys[key] = glfwGetKey(s_Window, key) == GLFW_PRESS;
        }
    }

    bool Input::IsKeyPressed(int key){
        if(key < 0 || key > GLFW_KEY_LAST){
            return false;
        }

        return s_CurrentKeys[key];
    }

    bool Input::IsKeyJustPressed(int key){
        if(key < 0 || key > GLFW_KEY_LAST){
            return false;
        }

        return s_CurrentKeys[key] && !s_PreviousKeys[key];
    }

    bool Input::IskeyJustReleased(int key){
        if(key < 0 || key > GLFW_KEY_LAST){
            return false;
        }

        return !s_CurrentKeys[key] && s_PreviousKeys[key];
    }
}