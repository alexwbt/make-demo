#include <iostream>

#include <axgl/window.h>
#include <axgl/gameloop.h>

class Game : public axgl::Gameloop
{
    bool Running() override
    {
        return axgl::Window::Running();
    }

    void Update() override
    {
        axgl::Window::Update();
    }

    void Render() override
    {
        axgl::Window::RenderAll();
    }
};

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
        std::cerr << error.what() << '\n';
        return -1;
    }

    return 0;
}
