#pragma once

#include "../Framework/Window.hpp"
#include "res/fonts.hpp"
#include "orbit.hpp"

const auto title = [](const auto& props){
  using namespace gx::render;

  for (int i = 0; i < 3; ++i){
    orbit++(
      gx::Rotation{ i * 120.f },
      gx::Position{ props.position },
      gx::State(props.state)
    );
  }

  const auto label = "Gacrux";

  gx::text++(
    gx::FontFamily{ &gx::fonts::consolas },
    gx::Label{{ label }},
    gx::Color{{ 1, 0.5, 0, 1 }},
    gx::Center(gx::Text::get_component_size(label), gx::Rect{ { 0, 170 }, gx::window::size })
  );
};
