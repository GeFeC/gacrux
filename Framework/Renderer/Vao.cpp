#include "Vao.hpp"

using gx::i32;

static constexpr i32 DEFAULT_VAO_STRIDE = 4;

namespace vao = gx::renderer::vao;

auto vao::create(const std::initializer_list<f32>& buffer) noexcept -> void{
  auto buffer_vec = std::vector<f32>(buffer);

  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);

  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

  glBufferData(
    GL_ARRAY_BUFFER, 
    buffer_vec.size() * sizeof(float), 
    buffer_vec.data(), GL_STATIC_DRAW
  );
}

auto vao::add_attrib_ptr(GLuint index, GLuint size, GLuint position) noexcept -> void{
  glVertexAttribPointer(
    index, 
    size, 
    GL_FLOAT, 
    GL_FALSE, 
    stride * sizeof(float), 
    (void*)(position * sizeof(float))
  );

  glEnableVertexAttribArray(index);
}