#include "Renderer.hpp"

#include "ShaderProgram.hpp"
#include "Vao.hpp"

#include "Shaders/fShader.hpp"
#include "Shaders/vShader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace renderer = gx::renderer;

auto renderer::init() -> void{
  namespace program = shader_program;

  vao::create({
    //vertex:  texture:
    0.f, 0.f, 0.f, 0.f,
    1.f, 0.f, 1.f, 0.f,
    1.f, 1.f, 1.f, 1.f,
    0.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 1.f,
    1.f, 1.f, 1.f, 1.f
  });

  vao::add_attrib_ptr(0, 2, 0);
  vao::add_attrib_ptr(1, 2, 2);

  program::create_program(shaders::v_shader, shaders::f_shader);
}

template<typename... Props>
static auto get_component_model(const gx::ComponentStyle<Props...>& component){
  const auto [x, y] = component.position;
  const auto [w, h] = component.size;

  const auto model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.f));
  return glm::scale(model, glm::vec3(w, h, 0.f));
}

template<typename... Props>
static auto get_rotatable_model(const gx::ComponentStyle<Props...>& component){
  const auto [x, y] = component.position;
  const auto [w, h] = component.size;
  const auto offset = component.rotation_offset;

  auto model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.f));
  model = glm::rotate(model, glm::radians(component.rotation), glm::vec3(0.f, 0.f, 1.f));
  model = glm::translate(model, glm::vec3(offset.x, offset.y, 0.f));
  return glm::scale(model, glm::vec3(w, h, 0.f));
}

auto renderer::draw(const gx::Component& component) noexcept -> void{
  namespace program = renderer::shader_program;

  program::set_uniform("model", get_component_model(component));
  program::set_uniform("f_color", component.color);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

auto renderer::draw(const gx::Rotatable& rotatable) noexcept -> void{
  namespace program = renderer::shader_program;

  program::set_uniform("model", get_rotatable_model(rotatable));
  program::set_uniform("f_color", rotatable.color);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

auto renderer::draw(const gx::Transformable& transformable) noexcept -> void{
  namespace program = renderer::shader_program;

  program::set_uniform("model", transformable.model.matrix);
  program::set_uniform("f_color", transformable.color);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

auto renderer::draw(const gx::TexturedComponent& component) noexcept -> void{
  namespace program = renderer::shader_program;

  program::set_uniform("model", get_component_model(component));
  program::set_uniform("f_color", component.color);
  program::set_uniform("is_texture", 1);
  component.texture->bind();
  component.texture->set_min_filter(component.min_filter);
  component.texture->set_mag_filter(component.mag_filter);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  program::set_uniform("is_texture", 0);
}

auto renderer::draw(const Text& text) -> void{
  namespace program = renderer::shader_program;
  program::set_uniform("is_glyph", 1);

  for (i32 i = 0; i < text.get_length(); ++i){
    auto current_char = text.get_text()[i];
    const auto& current_glyph_texture = text.get_font()->glyphs[current_char].texture;
    
    current_glyph_texture.bind();  
    
    renderer::draw(text.get_glyph(i));
  }
  program::set_uniform("is_glyph", 0);
}