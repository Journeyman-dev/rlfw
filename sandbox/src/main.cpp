
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

#include <iostream>
#include <rlfw/rlfw.hpp>
#include <rlm/cellular/ostream.hpp>
#include <rlm/linear/ostream.hpp>
#include <stdexcept>
#include <variant>

class MyApp : public rl::App
{
  public:
    // Called before the window is created. You can configure how it will be created by calling setter functions.
    void OnAppStart() override
    {
      rl::set_window_size(512, 512);
      rl::set_window_title("My App Window");
      rl::set_window_resizable(true);
    }

    // Called right after window is created. Graphics resources can be loaded here.
    void OnLoadResources() override
    {
      
    }

    // Called at the start of every update frame, before any events have been processed.
    void OnFrameStart() override
    {

    }

    // Called when a window resize event is processed.
    void OnFramebufferSize(const rl::cell_vector2<int>& size) override
    {
      // The size getter is updated after this function is finished, so it can be used to get the size from before.
      const auto previous_size = rl::get_window_size();
      const auto size_change = size - previous_size;
      std::cout << "framebuffer size changed. Previous size: " << previous_size << " new size: " << size << " Change amount: " << size_change << std::endl;
    }

    // Called when a mouse button event is processed.
    void OnMouseButton(rl::MouseButton button, bool pressed) override
    {

    }
    
    // Called when a mouse position event is processed.
    void OnMousePosition(const rl::vector2<double>& position) override
    {
      //std::cout << "mouse position: " << position << std::endl;
    }
    
    // Called when a mouse enter event is processed.
    void OnMouseEnter(bool entered) override
    {
      if (entered)
      {
        std::cout << "mouse entered" << std::endl;
      }
      else
      {
        std::cout << "mouse left" << std::endl;
      }
    }
    
    // Called when a mouse scroll event is processed.
    void OnMouseScroll(const rl::vector2<double>& translation) override
    {

    }
    
    // Called when a keyboard key event is processed.
    void OnKeyboardKey(rl::KeyboardKey key, bool pressed) override
    {
      // pressing the escape key closes the window
      if (key == rl::KeyboardKey::Escape && pressed)
      {
        rl::force_close();
      }
      // pressing the r key with ctrl pressed toggles the window being resizable by dragging the edges
      else if (
        key == rl::KeyboardKey::R &&
        pressed &&
        rl::get_ctrl_pressed())
      {
        rl::set_window_resizable(!rl::get_window_resizable());
      }
      // pressing z while holding f will toggle window decorations
      else if (
        key == rl::KeyboardKey::Z &&
        pressed &&
        rl::get_pressed(rl::KeyboardKey::F)
      )
      {
        rl::set_window_decorated(!rl::get_window_decorated());
      }
    }
    
    // Called when a keyboard character event is processed.
    void OnKeyboardCharacter(unsigned int codepoint) override
    {

    }
    
    // Called when the window is manually closed or rl::try_close() was called. rl::force_close() bypasses this.
    bool OnTryClose() override
    {
      // returning false means x button does not close the window
      return false;
    }
    
    // Do all game state updates. This is called before everything is drawn and after all events are processed.
    void OnUpdate() override
    {

    }
    
    // Do update stuff after drawing is done.
    void OnPostDraw() override
    {

    }
    
    // Called right before the application closes.
    void OnAppStop() override
    {

    }
};

int main()
{
  try
  {
    MyApp my_app;
    rl::run(my_app);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
