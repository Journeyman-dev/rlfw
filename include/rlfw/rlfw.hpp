
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

#include <rlm/cellular/cell_vector2.hpp>
#include <string>
#include <rlfw/App.hpp>

namespace rl
{
    void run(rl::App& app);
    bool get_is_running() noexcept;
    void try_close();
    void force_close();
    std::string_view get_window_title();
    void set_window_title(std::string_view title);
    void set_window_size(const rl::cell_vector2<int>& size);
    void set_window_size(int width, int height);
    rl::cell_vector2<int> get_window_size();
    void set_window_visible(bool visible);
    bool get_window_visible();
    void set_window_resizable(bool resizable);
    bool get_window_resizable();
    void set_window_decorated(bool decorated);
    bool get_window_decorated();
    bool get_mouse_entered();
    bool get_pressed(rl::MouseButton button);
    bool get_pressed(rl::KeyboardKey key);
    bool get_ctrl_pressed();
    bool get_alt_pressed();
    bool get_shift_pressed();
    bool get_super_pressed();
}
