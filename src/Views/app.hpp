#pragma once

#include "Components/title.hpp"

#include "Models/app.hpp"
#include "Controllers/app.hpp"

#include "res/textures.hpp"

auto app_res = gx::Resources(
  gx::FontList{
    std::make_pair(&gx::fonts::consolas, 70)
  },
  gx::TextureList{}
);

auto app = gx::make_view<AppController>([]{
  gx::component(gx::Size(gx::window_size.x, gx::window_size.y), gx::Color(0.1, 0.05, 0, 1));

  title(
    gx::Size(800, 600), 
    gx::Center(gx::Vec2(0, 0), gx::window_size)
  );
}, app_res);