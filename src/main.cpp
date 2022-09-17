#include <../Framework/Window.hpp>
#include <../Framework/Components/Components.hpp>

#include "res/fonts.hpp"
#include "Views/app.hpp"

#include <iostream>

auto main() -> int{
  try{
    gx::window::init_gl();
    gx::window::set_title("My Gacrux App");
    gx::window::set_size(gx::Vec2(800, 600));
    gx::window::render(app);
  }catch(gx::Exception& e){
    std::cerr << e.what();
  }
}