#pragma once

#include "Drawable/Component.hpp"
#include "Drawable/Text.hpp"

namespace gx::renderer{
  inline GLuint shader_program_id;

  auto init() -> void;
  auto draw(const Component& component) noexcept -> void;
  auto draw(const Rotatable& component) noexcept -> void;
  auto draw(const Transformable& component) noexcept -> void;
  auto draw(const TexturedComponent& component) noexcept -> void;
  auto draw(const Text& text) -> void;
}