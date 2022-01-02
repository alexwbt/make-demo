#include "axgl/window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace axgl
{
    /* Static */

    bool Window::initialized_ = false;
    bool Window::terminated_ = false;
    bool Window::initialized_glad_ = false;

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

        for (const auto &[glfw_window, window] : windows_)
            window->Destroy();

        glfwTerminate();
        terminated_ = true;
    }

    bool Window::Running()
    {
        for (const auto &[glfw_window, window] : windows_)
            if (!glfwWindowShouldClose(glfw_window))
                return true;
        return false;
    }

    void Window::Update()
    {
        // destroy closed windows
        for (auto it = windows_.begin(); it != windows_.end();)
        {
            const auto &glfw_window = it->first;
            const auto &window = it->second;
            if (window->destroyed_ || glfwWindowShouldClose(glfw_window))
            {
                it->second->Destroy();
                it = windows_.erase(it);
            }
            else
                ++it;
        }

        glfwPollEvents();
    }

    void Window::RenderAll()
    {
        for (const auto &[glfw_window, window] : windows_)
        {
            glfwMakeContextCurrent(glfw_window);
            window->Render();
            glfwSwapBuffers(glfw_window);
        }
    }

    void Window::CursorPosCallback(GLFWwindow *glfw_window, double x, double y)
    {
        auto *window = GetWindow(glfw_window);
        if (window && window->event_listener_)
            window->event_listener_->MouseMove(x, y);
    }

    void Window::MouseButtonCallback(GLFWwindow *glfw_window, int button, int action, int mods)
    {
        auto *window = GetWindow(glfw_window);
        if (window && window->event_listener_)
            window->event_listener_->MouseDown(button);
    }

    void Window::KeyCallback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods)
    {
        auto *window = GetWindow(glfw_window);
        if (!window || !window->event_listener_)
            return;

        switch (action)
        {
        case GLFW_PRESS:
            window->event_listener_->KeyDown(key);
            break;
        case GLFW_RELEASE:
            window->event_listener_->KeyUp(key);
            break;
        }
    }

    void Window::FramebufferSizeCallback(GLFWwindow *glfw_window, int width, int height)
    {
        auto *window = GetWindow(glfw_window);
        if (window && window->event_listener_)
            window->event_listener_->Resized(width, height);
    }

    Window *Window::GetWindow(GLFWwindow *glfw_window)
    {
        try
        {
            return windows_.at(glfw_window);
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Tried to get GLFW window that does bot exists." << std::endl;
            return nullptr;
        }
    }

    /* Non-static */

    Window::Window(int width, int height, const std::string &title)
    {
        if (!initialized_ || terminated_)
            throw std::runtime_error("Failed to create window, GLFW not initialized.");

        glfw_window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!glfw_window_)
            throw std::runtime_error("Failed to create window " + title + ".");

        glfwMakeContextCurrent(glfw_window_);

        glfwSetCursorPosCallback(glfw_window_, Window::CursorPosCallback);
        glfwSetMouseButtonCallback(glfw_window_, Window::MouseButtonCallback);
        glfwSetKeyCallback(glfw_window_, Window::KeyCallback);
        glfwSetFramebufferSizeCallback(glfw_window_, Window::FramebufferSizeCallback);

        if (!initialized_glad_)
        {
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                throw std::runtime_error("Failed to initialize GLAD.");
            initialized_glad_ = true;
        }

        windows_.insert({glfw_window_, this});
    }

    Window::~Window()
    {
        Destroy();
    }

    void Window::SetEventListener(std::shared_ptr<EventListener> event_listener)
    {
        event_listener_ = std::move(event_listener);
    }

    void Window::SetRenderer(std::shared_ptr<Renderer> renderer)
    {
        renderer_ = std::move(renderer);
    }

    void Window::SetTitle(const std::string &title)
    {
        glfwSetWindowTitle(glfw_window_, title.c_str());
    }

    void Window::Render()
    {
        if (renderer_)
            renderer_->Render();
    }

    void Window::Destroy()
    {
        if (!destroyed_)
        {
            glfwDestroyWindow(glfw_window_);
            destroyed_ = true;
        }
    }

}
