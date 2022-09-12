#pragma once

#include "Props/orbit.hpp"

const auto orbit = gx::make_component<gx::Rotation, ParticleRotation>([](const auto& props){
  for (int i = 0; i < 5; ++i){
    gx::transformable(
      gx::Model(
        gx::Mat4()
        .translate(gx::Vec2(400, 250))
        .rotate(props.rotation)
        .translate(gx::Vec2(0, -80))
        .scale(gx::Vec2(1, 1.6))
        .rotate(props.particle_rotation + i * 40)
        .translate(gx::Vec2(60, 0))
        .rotate(-(props.particle_rotation + i * 40))
        .scale(gx::Vec2(15 - i, (15 - i) / 1.6))
        .rotate(props.particle_rotation + i * 40)
      ),
      gx::Color(1, 0.5, 0, 1)
    );
  }
});