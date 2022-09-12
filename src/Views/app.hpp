#pragma once

#include "../Framework/Components/Props.hpp"
#include "../Framework/Components/Components.hpp"
#include "../Framework/Components/CustomComponents.hpp"
#include "../Framework/Views/View.hpp"

#include "Components/orbit.hpp"
#include "Models/app.hpp"
#include "Controllers/app.hpp"
#include "Props/orbit.hpp"

auto app_fonts = gx::FontList{
  std::make_pair(&gx::fonts::consolas, 70)
};

auto app = gx::make_view<AppModel, AppController>([](const auto& model){
  gx::component(gx::Size(800, 600), gx::Color(0.1, 0.05, 0, 1));

  for (int i = 0; i < 360; i += 120){
    orbit(
      gx::Rotation(model.orbit_rotation + i), 
      ParticleRotation(model.particle_rotation)
    );
  }

  gx::text("Gacrux", 
    gx::Color(1, 0.5, 0, 1), 
    gx::FontFamily(gx::fonts::consolas),
    gx::Position(280, 470)
  );
}, app_fonts);