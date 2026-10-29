#include "Renderer.h"
#include <GLFW/glfw3.h>

namespace Nova{
    void Renderer::Clear(float red, float green, float blue, float alpha){
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}