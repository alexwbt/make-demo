#include <iostream>
#include <memory>

#include "game.h"

int main()
{
    try
    {
        axgl::Window::InitializeGlfw();

        auto game = std::make_shared<Game>();
        axgl::Window window(800, 600, "axgl demo");
        window.SetEventListener(game);

        game->Run();

        axgl::Window::TerminateGlfw();
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
        return -1;
    }

    return 0;
}
