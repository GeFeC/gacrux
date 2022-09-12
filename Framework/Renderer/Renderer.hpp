#pragma once

#include "Drawable/Component.hpp"
#include "Drawable/Text.hpp"

namespace gx::renderer{
  inline GLuint shader_program_id;

  auto init() -> void;
  auto draw(const gx::Component& component) noexcept -> void;
  auto draw(const gx::Rotatable& component) noexcept -> void;
  auto draw(const gx::Transformable& transformable) noexcept -> void;
  auto draw(const Text& text) -> void;
}