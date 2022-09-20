#include <../Framework/Window.hpp>
#include <../Framework/Components/Render.hpp>

#include "Views/app.hpp"

auto main() -> int{
  gx::window::init_gl();
  gx::window::set_title("Tytul okna");
  gx::window::set_size(gx::Vec2(800, 600));
  gx::window::render(app);
}