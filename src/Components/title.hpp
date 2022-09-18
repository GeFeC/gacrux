#pragma once

#include "res/fonts.hpp"
#include "orbit.hpp"

const auto title = gx::make_component([](const auto& props){
  for (int i = 0; i < 360; i += 120){
    orbit(
      gx::Rotation(AppModel::orbit_rotation + i),
      gx::Position(props.position.x, props.position.y)
    );
  }

  gx::text(
    gx::FontFamily(&gx::fonts::consolas),
    gx::Label("Gacrux"), 
    gx::Color(1, 0.5, 0, 1), 
    gx::Center(gx::Vec2(0, 190), gx::window::size)
  );
});