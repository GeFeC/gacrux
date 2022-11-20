#pragma once

#include "States/AppState.hpp"
#include "../Framework/Frames/Frame.hpp"

static auto app_controller = [](AppState& state){
  state.orbit_rotation -= gx::delta_time * 45;
  state.particle_rotation -= gx::delta_time * 140;
};
