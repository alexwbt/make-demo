#include <iostream>

#include <axgl/window.h>

int main()
{
    try
    {
        axgl::Window::InitializeGlfw();

        axgl::Window window(800, 600, "axgl demo");

        // gameloop
        constexpr int64_t kOneSecond = 1000000000;
        constexpr double kTimeStep = kOneSecond / 60.0;

        auto start_time = std::chrono::high_resolution_clock::now();
        double delta_time = 0.0;

        while (axgl::Window::Running())
        {
            auto now = std::chrono::high_resolution_clock::now();
            delta_time += static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time).count()) / kTimeStep;
            start_time = now;

            bool did_update = delta_time >= 1;

            while (delta_time >= 1)
            {
                // update
                delta_time--;
            }

            if (did_update)
                axgl::Window::RenderAll();

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
