#include "axgl/window.h"

#include <string>

#include <GLFW/glfw3.h>

namespace axgl
{
    /* Static */

    bool Window::initialized_ = false;
    bool Window::terminated_ = false;

    std::unordered_map<GLFWwindow *, Window *> Window::windows_;

    void Window::InitializeGlfw()
    {
        if (initialized_ || terminated_)
            return;

        if (!glfwInit())
            throw std::runtime_error("Failed to init GLFW.");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        initialized_ = true;
    }

    void Window::TerminateGlfw()
    {
        if (!initialized_ || terminated_)
            return;
        glfwTerminate();
        terminated_ = true;
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    bool Window::Running()
    {
        bool running = false;
        for (auto it = windows_.begin(); it != windows_.end();)
        {
            const auto &glfw_window = it->first;
            const auto &window = it->second;
            if (glfwWindowShouldClose(glfw_window))
            {
                window->Destroy();
                it = windows_.erase(it);
            }
            else
            {
                running = true;
                ++it;
            }
        }
        return running;
    }

    /* Non-static */

    Window::Window(int width, int height, const std::string &title)
    {
        glfw_window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!glfw_window_)
            throw std::runtime_error("Failed to create window " + title + ".");

        glfwMakeContextCurrent(glfw_window_);
        // glfwSetKeyCallback(window, GlfwManager::KeyCallback);
        // glfwSetCursorPosCallback(window, GlfwManager::MouseCallback);
        // glfwSetFramebufferSizeCallback(window, GlfwManager::ResizeCallback);

        windows_.insert({glfw_window_, this});
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::Destroy()
    {
        if (!destroyed_)
        {
            windows_.erase(glfw_window_);
            glfwDestroyWindow(glfw_window_);
            destroyed_ = true;
        }
    }

}
