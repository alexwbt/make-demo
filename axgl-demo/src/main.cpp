#include <iostream>

#include "game.h"

int main()
{
    try
    {
        axgl::Window::InitializeGlfw();

        axgl::Window window(800, 600, "axgl demo");

        Game game;
        game.Run();

        axgl::Window::TerminateGlfw();
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
        return -1;
    }

    return 0;
}
