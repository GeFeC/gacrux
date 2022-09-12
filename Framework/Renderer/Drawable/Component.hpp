#pragma once
#include "../../aliases.hpp"
#include "../../Util/Math.hpp"

#include <glm/glm.hpp>

namespace gx{

struct Component{
  gx::Vec2 position = { 0.f, 0.f };
  gx::Vec2 size = { 0.f, 0.f };
  glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
};

struct Rotatable : Component{
  gx::f32 rotation = 0.f;
  gx::Vec2 rotation_offset = { 0.f, 0.f };
};

struct Transformable{
  gx::Mat4 model;
  glm::vec4 color = { 1.f, 1.f, 1.f, 1.f };
};

}