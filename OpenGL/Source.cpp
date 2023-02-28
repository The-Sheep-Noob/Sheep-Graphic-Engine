#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "shapes.h"
#include "settings.h"


int main() {

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(swap_interval);
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Sheep Rendering-Engine", NULL , NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "wth bro !" << std::endl;
    }

    Square testing;
    testing.setColors(100);
    testing.Size = (height > width ? height : width);
    testing.setPositions(350);

    Square testing2;
    testing2.A = 0;
    testing2.Size = 300;
    testing2.setPositions(350);
    testing2.Texture = "Lightning.png";

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        testing2.Y_rotate += 1;

        Shapes::renderShapes();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();

    return 0;
}
