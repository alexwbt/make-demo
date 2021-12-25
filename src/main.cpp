#include <iostream>

#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw." << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Failed to create window." << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
