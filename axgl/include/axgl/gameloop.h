#pragma once

#include <chrono>

namespace axgl
{
    class Gameloop
    {
    public:
        virtual ~Gameloop() {}

        void Run();
        virtual double Loop(double delta_time);

        virtual bool Running() { return false; }
        virtual void Update() {}
        virtual void Render() {}
    };
}
