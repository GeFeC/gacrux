#include "../Framework/Window.hpp"
#include "../Framework/Components/Components.hpp"
#include "res/fonts.hpp"

#include "Views/app.hpp"

#include <iostream>

auto main() -> int{
  try{
    gx::make_app("First Gacrux App", gx::Vec2(800, 600), app);
  }catch(gx::Exception& e){
    std::cerr << e.what();
  }
}