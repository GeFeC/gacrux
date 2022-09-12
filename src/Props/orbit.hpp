#pragma once

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Math.hpp"

struct ParticleRotation{ 
  gx::f32 particle_rotation;

  ParticleRotation() = default;
  ParticleRotation(gx::f32 r) : particle_rotation{ r } {}

  template<typename T>
  auto set_to(T& item) const{
    item.particle_rotation = particle_rotation;
  }
};