
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

#include <rlfw/App.hpp>

void rl::App::OnAppStart()
{
}

void rl::App::OnLoadResources()
{

}

void rl::App::OnFrameStart()
{
}

void rl::App::OnFramebufferSize(const rl::cell_vector2<int>& size)
{
}

void rl::App::OnMouseButton(rl::MouseButton button, bool pressed)
{
}

void rl::App::OnMousePosition(const rl::vector2<double>& position)
{
}

void rl::App::OnMouseEnter(bool entered)
{
}

void rl::App::OnMouseScroll(const rl::vector2<double>& translation)
{
}

void rl::App::OnKeyboardKey(rl::KeyboardKey key, bool pressed)
{
}

void rl::App::OnKeyboardCharacter(unsigned int codepoint)
{
}

bool rl::App::OnTryClose()
{
    return true;
}

void rl::App::OnUpdate()
{
}

void rl::App::OnPostDraw()
{
}

void rl::App::OnAppStop()
{
}
