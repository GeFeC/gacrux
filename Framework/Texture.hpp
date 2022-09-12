#pragma once

#include "aliases.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

namespace gx{

struct Texture{
private:
  static constexpr i32 FORMAT = GL_RGBA;

  std::string source_path;

  auto generate_() noexcept -> void;
  auto read_from_source_path_and_load_() const -> void;

public:
  GLuint id;

  Texture() noexcept = default;

  explicit Texture(const std::string& path) noexcept;
  explicit Texture(GLuint id) noexcept : id(id) {}
  
  auto allocate() -> void;
  auto free() noexcept -> void;

  auto set_min_filter(i32 min_filter) const noexcept -> void;
  auto set_mag_filter(i32 mag_filter) const noexcept -> void;

  auto bind() const noexcept -> void;
};

}