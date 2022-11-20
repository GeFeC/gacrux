#pragma once

#include "aliases.hpp"
#include "Frames/Frame.hpp"

namespace gx::animation{
  constexpr auto run(f32* target, f32 aim, f32 speed){
    auto& value = *target;
    if (value == aim) return;

    const auto sign = (value < aim) * 2 - 1;
    const auto boost = gx::delta_time * speed * sign;
    value += boost;

    if (aim - value == gx::in_range(-boost, boost)){
      value = aim;
    }
  }
}
