#pragma once

#include "res/fonts.hpp"

struct AppController{
  static inline auto setup = [](auto& model){};

  static inline auto loop = [](auto& model){
    model.orbit_rotation -= gx::delta_time * 45;
    model.particle_rotation -= gx::delta_time * 140;
  };
};