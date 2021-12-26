
#include <axgl/window.h>

int main()
{
    axgl::Window::InitializeGlfw();

    axgl::Window window(800, 600, "Playground");

    while (axgl::Window::Running())
    {
        axgl::Window::PollEvents();
    }

    axgl::Window::TerminateGlfw();

    return 0;
}
