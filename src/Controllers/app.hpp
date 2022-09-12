#pragma once

#include "Models/app.hpp"

struct AppController{
  static auto setup(){};

  static auto loop(){
    AppModel::orbit_rotation -= gx::delta_time * 45;
    AppModel::particle_rotation -= gx::delta_time * 140;
  };
};