#include<iostream>
#include<GLFW/glfw3.h>

int main(){
    //initialize GLFW
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    //Configure the OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Required for macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the application window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Nova2D - Our First Window", nullptr, nullptr);

    if(window == nullptr){
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    //Enable VSync
    glfwSwapInterval(1);

    //Main game loop
    while (!glfwWindowShouldClose(window)){

        //Process window events
        glfwPollEvents();

        //Set the background color
        glClearColor(0.10f, 0.12f, 0.16f, 1.0f);

        //Clear the previous fream
        glClear(GL_COLOR_BUFFER_BIT);

        //Display the rendered Frame
        glfwSwapBuffers(window);
    }

    //Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout<<" Nova2D shut down successfully!\n";
    return 0;
}