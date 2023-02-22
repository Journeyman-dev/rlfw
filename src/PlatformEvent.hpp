
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

#pragma once

#include <rlfw/KeyboardKey.hpp>
#include <rlfw/MouseButton.hpp>
#include <rlm/cellular/cell_vector2.hpp>
#include <rlm/linear/vector2.hpp>
#include <variant>

namespace rl
{
    struct FramebufferSizeEvent
    {
        rl::cell_vector2<int> size;
    };
    struct MouseButtonEvent
    {
        rl::MouseButton mouse_button;
        bool pressed;
    };
    struct MousePositionEvent
    {
        rl::vector2<double> position;
    };
    struct MouseEnterEvent
    {
        bool entered;
    };
    struct MouseScrollEvent
    {
        rl::vector2<double> translation;
    };
    struct KeyboardKeyEvent
    {
        rl::KeyboardKey keyboard_key;
        bool pressed;
    };
    struct KeyboardCharacterEvent
    {
        unsigned int codepoint;
    };
    struct WindowCloseEvent {};
    using PlatformEvent = std::variant<
            FramebufferSizeEvent,
            MouseButtonEvent,
            MousePositionEvent,
            MouseEnterEvent,
            MouseScrollEvent,
            KeyboardKeyEvent,
            KeyboardCharacterEvent,
            WindowCloseEvent
    >;
}
