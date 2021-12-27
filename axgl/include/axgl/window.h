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
            virtual void Render() = 0;
        };

    private:
        static bool initialized_;
        static bool terminated_;
        static bool initialized_glad_;

        static std::unordered_map<GLFWwindow *, Window *> windows_;

    public:
        static void InitializeGlfw();
        static void TerminateGlfw();
        static bool Running();
        static void Update();
        static void RenderAll();

    private:
        GLFWwindow *glfw_window_;

        std::shared_ptr<EventListener> event_listener_;
        std::shared_ptr<Renderer> renderer_;

        bool destroyed_ = false;

    public:
        Window(int width, int height, const std::string &title);
        ~Window();

    public:
        void SetEventListener(std::shared_ptr<EventListener> event_listener);
        void SetRenderer(std::shared_ptr<Renderer> renderer);

        void SetTitle(const std::string& title);

    private:
        void Render();
        void Destroy();
    };
}
