#include <../Framework/Window.hpp>
#include <../Framework/Components/Render.hpp>

#include "res/fonts.hpp"
#include "Frames.hpp"

auto main() -> int{
  gx::window::init_gl();
  gx::window::set_title("First gacrux app!");
  gx::window::set_size(gx::Vec2(800, 600));

  gx::window::render(frame_manager);
}
