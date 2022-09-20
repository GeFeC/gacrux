#pragma once

#include "../Framework/Components/Components.hpp"
#include "../Framework/Components/Text.hpp"

namespace gx::renderer{
  inline GLuint shader_program_id;

  auto init() -> void;
  auto draw(const Text& text) -> void;
  auto draw(const Component& component) noexcept -> void;
  auto draw(const Rotatable& component) noexcept -> void;
  auto draw(const Transformable& component) noexcept -> void;
  auto draw(const TexturedComponent& component) noexcept -> void;
}