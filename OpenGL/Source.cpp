#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "program.h"
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

    Program main_program;
    main_program.onStartup();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        main_program.onUpdate();
        main_program.renderShapes();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    main_program.clearObjects();
    glfwTerminate();

    return 0;
}
