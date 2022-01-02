#pragma once

#include <axgl/window.h>
#include <axgl/gameloop.h>

class Game
    : public axgl::Gameloop,
      public axgl::Window::EventListener,
      public axgl::Window::Renderer
{
    bool Running() override
    {
        return axgl::Window::Running();
    }

    void MouseMove(double x, double y) override
    {
        std::cout << "Mouse Moved: " << x << ' ' << y << std::endl;
    }

    void Update() override
    {
        axgl::Window::Update();
    }

    void DidUpdate() override
    {
        axgl::Window::RenderAll();
    }

    void Render() override
    {
    }
};
