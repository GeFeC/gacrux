#pragma once

#include "../Framework/aliases.hpp"

#include <glad/glad.h>
#include <vector>

namespace gx::renderer::vao{
  inline GLuint vao_id;
  inline GLuint vbo_id;
  inline i32 stride = 4;

  auto create(const std::initializer_list<f32>& buffer) noexcept -> void;
  auto add_attrib_ptr(GLuint index, GLuint size, GLuint position) noexcept -> void;
}