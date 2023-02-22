
// SPDX-FileCopyrightText: 2023 Daniel Aimé Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: MIT

/*
    Copyright (c) 2023 Daniel Aimé Valcour
    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <rlfw/rlfw.hpp>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <rlm/cellular/cell_vector2.hpp>
#include "PlatformEvent.hpp"
#include <vector>
#include <rlfw/App.hpp>
#include <bitset>

struct WindowInfo
{
    bool is_running = false;
    GLFWwindow* window = nullptr;
    std::string title = "";
    rl::cell_vector2<int> size = rl::cell_vector2<int>(600, 400);
    bool visible = true;
    bool resizable = false;
    bool decorated = true;
    std::vector<rl::PlatformEvent> events;
    rl::App* app;
    bool force_close = false;
    bool mouse_entered = false;
    std::bitset<348> keyboard_keys;
    std::bitset<8> mouse_buttons;
    rl::vector2<double> mouse_position = rl::vector2<double>();
};

static WindowInfo sWINDOW_INFO;

void throw_glfw_error()
{
    const char* glfw_error;
    glfwGetError(&glfw_error);
    throw std::runtime_error(glfw_error);
}

bool is_initialized()
{
    return sWINDOW_INFO.window != nullptr;
}

void terminate() noexcept
{
    if (sWINDOW_INFO.window != nullptr)
    {
        glfwDestroyWindow(sWINDOW_INFO.window);
        sWINDOW_INFO.window = nullptr;
    }
    glfwTerminate();
    sWINDOW_INFO = WindowInfo();
}

void rl::run(rl::App& app)
{
    if (rl::get_is_running())
    {
        throw std::runtime_error("rlfw is already running");
    }
    sWINDOW_INFO.is_running = true;
    app.OnAppStart();
    if (!glfwInit())
    {
        throw_glfw_error();
    }
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_VISIBLE, sWINDOW_INFO.visible);
    glfwWindowHint(GLFW_RESIZABLE, sWINDOW_INFO.resizable);
    glfwWindowHint(GLFW_DECORATED, sWINDOW_INFO.decorated);
    sWINDOW_INFO.window = glfwCreateWindow(sWINDOW_INFO.size.x, sWINDOW_INFO.size.y, sWINDOW_INFO.title.data(), NULL, NULL);
    if (!sWINDOW_INFO.window)
    {
        glfwTerminate();
        throw_glfw_error();
    }
    glfwMakeContextCurrent(sWINDOW_INFO.window);
    app.OnLoadResources();
    glfwSetFramebufferSizeCallback(
      sWINDOW_INFO.window,
      [](GLFWwindow* window, int width, int height)
      {
        rl::FramebufferSizeEvent event;
        event.size = rl::cell_vector2<int>(width, height);
        sWINDOW_INFO.events.push_back(event);
      }
    );
    glfwSetMouseButtonCallback(
      sWINDOW_INFO.window,
      [](GLFWwindow* window, int button, int action, int mods)
      {
        rl::MouseButtonEvent event;
        event.mouse_button = static_cast<rl::MouseButton>(button);
        event.pressed = action;
        sWINDOW_INFO.events.push_back(event);
      }
    );
    glfwSetCursorPosCallback(
      sWINDOW_INFO.window,
      [](GLFWwindow* window, double xpos, double ypos)
      {
        rl::MousePositionEvent event;
        event.position = rl::vector2<double>(xpos, ypos);
        sWINDOW_INFO.events.push_back(event);
      }
    );
    glfwSetCursorEnterCallback(
      sWINDOW_INFO.window,
      [](GLFWwindow* window, int entered)
      {
        rl::MouseEnterEvent event;
        event.entered = entered;
        sWINDOW_INFO.events.push_back(event);
      }
    );
    glfwSetScrollCallback(
        sWINDOW_INFO.window,
        [](GLFWwindow* window, double x_translation, double y_translation)
        {
            rl::MouseScrollEvent event;
            event.translation = rl::vector2<double>(x_translation, y_translation);
            sWINDOW_INFO.events.push_back(event);
        }
    );
    glfwSetKeyCallback(
        sWINDOW_INFO.window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            rl::KeyboardKeyEvent event;
            event.keyboard_key = static_cast<rl::KeyboardKey>(key);
            event.pressed = action;
            sWINDOW_INFO.events.push_back(event);
        }
    );
    glfwSetCharCallback(
        sWINDOW_INFO.window,
        [](GLFWwindow* window, unsigned int codepoint)
        {
            rl::KeyboardCharacterEvent event;
            event.codepoint = codepoint;
            sWINDOW_INFO.events.push_back(event);
        }
    );
    glfwSetWindowCloseCallback(
        sWINDOW_INFO.window,
        [](GLFWwindow* window)
        {
            rl::WindowCloseEvent event;
            sWINDOW_INFO.events.push_back(event);
        }
    );
    sWINDOW_INFO.force_close = false;
    bool should_close = false;
    while (!should_close && !sWINDOW_INFO.force_close)
    {
        app.OnFrameStart();
        glfwPollEvents();
        for (const auto& event_v : sWINDOW_INFO.events)
        {
            if (std::holds_alternative<rl::FramebufferSizeEvent>(event_v))
            {
                const auto& event = std::get<rl::FramebufferSizeEvent>(event_v);
                app.OnFramebufferSize(event.size);
                sWINDOW_INFO.size = event.size;
            }
            else if (std::holds_alternative<rl::MouseButtonEvent>(event_v))
            {
                const auto& event = std::get<rl::MouseButtonEvent>(event_v);
                app.OnMouseButton(event.mouse_button, event.pressed);
                sWINDOW_INFO.mouse_buttons.set(
                    static_cast<std::size_t>(event.mouse_button),
                    event.pressed
                );               
            }
            else if (std::holds_alternative<rl::MouseEnterEvent>(event_v))
            {
                const auto& event = std::get<rl::MouseEnterEvent>(event_v);
                app.OnMouseEnter(event.entered);
                sWINDOW_INFO.mouse_entered = event.entered;
            }
            else if (std::holds_alternative<rl::MousePositionEvent>(event_v))
            {
                const auto& event = std::get<rl::MousePositionEvent>(event_v);
                app.OnMousePosition(event.position);
                sWINDOW_INFO.mouse_position = event.position;
            }
            else if (std::holds_alternative<rl::MouseScrollEvent>(event_v))
            {
                const auto& event = std::get<rl::MouseScrollEvent>(event_v);
                app.OnMouseScroll(event.translation);
            }
            else if (std::holds_alternative<rl::KeyboardKeyEvent>(event_v))
            {
                const auto& event = std::get<rl::KeyboardKeyEvent>(event_v);
                app.OnKeyboardKey(event.keyboard_key, event.pressed);
                sWINDOW_INFO.keyboard_keys.set(
                    static_cast<std::size_t>(event.keyboard_key) - 1,
                    event.pressed
                );               
            }
            else if (std::holds_alternative<rl::KeyboardCharacterEvent>(event_v))
            {
                const auto& event = std::get<rl::KeyboardCharacterEvent>(event_v);
                app.OnKeyboardCharacter(event.codepoint);
            }
            else if (std::holds_alternative<rl::WindowCloseEvent>(event_v))
            {
                should_close = app.OnTryClose();
            }
        }
        sWINDOW_INFO.events.clear();
        app.OnUpdate();
        // dispatch draw thread
        app.OnPostDraw();
    }
    app.OnAppStop();
    terminate();
}

bool rl::get_is_running() noexcept
{
    return sWINDOW_INFO.is_running;
}

void rl::try_close()
{
    sWINDOW_INFO.events.push_back(rl::WindowCloseEvent());
}

void rl::force_close()
{
    sWINDOW_INFO.force_close = true;
}

std::string_view rl::get_window_title()
{
    return sWINDOW_INFO.title;
}

void rl::set_window_title(std::string_view title)
{
    if (is_initialized())
    {
        glfwSetWindowTitle(sWINDOW_INFO.window, title.data());
    }
    sWINDOW_INFO.title = title;
}

void rl::set_window_size(const rl::cell_vector2<int>& size)
{
    if (is_initialized())
    {
        glfwSetWindowSize(sWINDOW_INFO.window, size.x, size.y);
    }
    sWINDOW_INFO.size = size;
}

void rl::set_window_size(int width, int height)
{
    rl::set_window_size(rl::cell_vector2<int>(width, height));
}

rl::cell_vector2<int> rl::get_window_size()
{
    return sWINDOW_INFO.size;
}

void rl::set_window_visible(bool visible)
{
    if (is_initialized())
    {
        if (visible)
        {
            glfwShowWindow(sWINDOW_INFO.window);
        }
        else
        {
            glfwHideWindow(sWINDOW_INFO.window);
        }
    }
    sWINDOW_INFO.visible = visible;
}

bool rl::get_window_visible()
{
    return sWINDOW_INFO.visible;
}

void rl::set_window_resizable(bool resizable)
{
    if (is_initialized())
    {
        glfwSetWindowAttrib(sWINDOW_INFO.window, GLFW_RESIZABLE, resizable);
    }
    sWINDOW_INFO.resizable = resizable;
}

bool rl::get_window_resizable()
{
    return sWINDOW_INFO.resizable;
}

void rl::set_window_decorated(bool decorated)
{
    if (is_initialized())
    {
        glfwSetWindowAttrib(sWINDOW_INFO.window, GLFW_DECORATED, decorated);
    }
    sWINDOW_INFO.decorated = decorated; 
}

bool rl::get_window_decorated()
{
    return sWINDOW_INFO.decorated;
}

bool rl::get_mouse_entered()
{
    return sWINDOW_INFO.mouse_entered;
}

bool rl::get_pressed(rl::MouseButton button)
{
    return sWINDOW_INFO.mouse_buttons.test(static_cast<std::size_t>(button));
}

bool rl::get_pressed(rl::KeyboardKey key)
{
    return sWINDOW_INFO.keyboard_keys.test(static_cast<std::size_t>(key) - 1);
}

bool rl::get_ctrl_pressed()
{
    return 
        rl::get_pressed(rl::KeyboardKey::LeftControl)||
        rl::get_pressed(rl::KeyboardKey::RightControl);
}

bool rl::get_alt_pressed()
{
    return 
        rl::get_pressed(rl::KeyboardKey::LeftAlt) ||
        rl::get_pressed(rl::KeyboardKey::RightAlt);
}

bool rl::get_shift_pressed()
{
    return 
        rl::get_pressed(rl::KeyboardKey::LeftShift) ||
        rl::get_pressed(rl::KeyboardKey::RightShift);
}

bool rl::get_super_pressed()
{
    return 
        rl::get_pressed(rl::KeyboardKey::LeftSuper) ||
        rl::get_pressed(rl::KeyboardKey::RightSuper);
}
