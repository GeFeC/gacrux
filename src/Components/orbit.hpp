#pragma once

#include <../Framework/Components/Render.hpp>
#include <../Framework/Views/View.hpp>

#include "Models/app.hpp"

const auto orbit = gx::make_component([](const auto& props){
  for (int i = 0; i < 5; ++i){
    gx::transformable(
      gx::Model(
        gx::Mat4()
        .translate(gx::Vec2(props.position.x + 400, props.position.y + 250))
        .rotate(props.rotation)
        .translate(gx::Vec2(0, -80))
        .scale(gx::Vec2(1, 1.6))
        .rotate(AppModel::particle_rotation + i * 40)
        .translate(gx::Vec2(60, 0))
        .rotate(-(AppModel::particle_rotation + i * 40))
        .scale(gx::Vec2(15 - i, (15 - i) / 1.6))
        .rotate(AppModel::particle_rotation + i * 40)
      ),
      gx::Color(1, 0.5, 0, 1 - 0.2 * i)
    );
  }
});