#pragma once

#include "Util/Math.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/ShaderProgram.hpp"

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

template<typename FrameManager>
auto render(const FrameManager& frame_manager){
  renderer::init();
  update_frame_buffer_(window::size);

  glfwShowWindow(gl_window);

  while(!glfwWindowShouldClose(gl_window)){
    frame_manager();
  }

  glfwTerminate();
}

}; //namespace gx

