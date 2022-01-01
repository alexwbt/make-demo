#include "axgl/gameloop.h"

namespace axgl
{
    static constexpr int64_t kOneSecond = 1000000000;
    static constexpr double kTimeStep = kOneSecond / 60.0;

    void Gameloop::Run()
    {
        auto start_time = std::chrono::high_resolution_clock::now();
        double delta_time = 0.0;
        while (Running())
        {
            auto now = std::chrono::high_resolution_clock::now();
            delta_time += static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time).count()) / kTimeStep;
            start_time = now;

            delta_time = Loop(delta_time);
        }
    }

    double Gameloop::Loop(double delta_time)
    {
        double output_delta_time = delta_time;

        while (output_delta_time >= 1)
        {
            Update();
            output_delta_time--;
        }

        if (delta_time >= 1)
            Render();

        return output_delta_time;
    }
}
