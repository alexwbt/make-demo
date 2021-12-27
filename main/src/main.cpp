#include <iostream>

#include <axgl/window.h>

int main()
{
    try
    {
        axgl::Window::InitializeGlfw();

        axgl::Window window(800, 600, "Playground");

        while (axgl::Window::Running())
        {
            axgl::Window::Update();
        }

        axgl::Window::TerminateGlfw();
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return -1;
    }

    return 0;
}
