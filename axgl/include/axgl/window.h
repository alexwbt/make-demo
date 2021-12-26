#pragma once

#include <unordered_map>
#include <memory>
#include <string>

struct GLFWwindow;

namespace axgl
{
    class Window final
    {
    public:
        struct EventListener
        {
            virtual ~EventListener() {}
        };

        struct Renderer
        {
            virtual ~Renderer() {}
        };

    private:
        static bool initialized_;
        static bool terminated_;

        static std::unordered_map<GLFWwindow *, Window *> windows_;

    public:
        static void InitializeGlfw();
        static void TerminateGlfw();
        static void PollEvents();
        static bool Running();

    private:
        GLFWwindow *glfw_window_;

        std::shared_ptr<EventListener> event_listener_;
        std::shared_ptr<Renderer> renderer_;

        bool destroyed_ = false;

    public:
        Window(int width, int height, const std::string &title);
        ~Window();

    private:
        void Destroy();
    };
}
