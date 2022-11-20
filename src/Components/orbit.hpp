#pragma once

#include <../Framework/Components/Render.hpp>
#include "../States/AppState.hpp"

const auto orbit = [](const auto& props){
  using namespace gx::render;

  const auto get_model = [&props = props](auto i){
    return gx::Mat4()
      .translate(gx::Vec2(props.position.x + 400, props.position.y + 250))
      .rotate(props.rotation)
      .translate(gx::Vec2(0, -80))
      .scale(gx::Vec2(1, 1.6))
      .rotate(props.state.particle_rotation + i * 40)
      .translate(gx::Vec2(60, 0))
      .rotate(-(props.state.particle_rotation + i * 40))
      .scale(gx::Vec2(15 - i, (15 - i) / 1.6))
      .rotate(props.state.particle_rotation + i * 40);
  };

  for (int i = 0; i < 5; ++i){
    gx::transformable++(
      gx::Model{{ get_model(i) }},
      gx::Color{{ 1, 0.5, 0, 1 - 0.2 * i }}
    );
  }
};
