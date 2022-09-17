#pragma once

#include "Util/Math.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Views/ViewManager.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

namespace gx::window{

inline GLFWwindow* gl_window;
inline Vec2 size;

auto update_frame_buffer_(const gx::Vec2& size) -> void;

auto init_gl() -> void;
auto set_title(const std::string& title) -> void;
auto set_size(const Vec2& size) -> void;

template<typename Controller, typename ViewFunction>
auto render(View<Controller, ViewFunction>& initial_view){
  renderer::init();
  update_frame_buffer_(window::size);

  glfwShowWindow(gl_window);

  gx::view_manager::current_view = &initial_view;
  gx::view_manager::run(gl_window);

  glfwTerminate();
}

}; //namespace gx

