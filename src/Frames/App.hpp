#pragma once

#include <../Framework/Components/Render.hpp>

#include "States/AppState.hpp"
#include "Controllers/AppController.hpp"

#include "res/fonts.hpp"

#include "Components/title.hpp"

const auto app_res = gx::Resources(
  gx::FontList{
    { &gx::fonts::consolas, 100 }
  },
  gx::TextureList{}
);

const auto app = gx::make_frame<AppState>([](const auto& state){
  using namespace gx::render;

  gx::component++(
    gx::Size{ gx::window::size },
    gx::Color{{ 0.1, 0.05, 0, 1 }}
  );

  title++(
    gx::Center({ 800, 600 }, gx::Rect{ { 0, 0 }, gx::window::size }),
    gx::State(state)
  );
}, app_res, app_controller);
