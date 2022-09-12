#pragma once

#include "Util/Math.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/ShaderProgram.hpp"
#include "Views/ViewManager.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

namespace gx{

GLFWwindow* window;

namespace literals{
  auto operator""_dt(unsigned long long value){
    return value * delta_time;
  }

  auto operator""_dt(long double value){
    return value * delta_time;
  }
}

auto update_frame_buffer(const Vec2& size){
  renderer::shader_program::set_uniform(
    "projection",
    glm::ortho(0.f, size.x, size.y, 0.f)
  );

  glViewport(0, 0, size.x, size.y);
}

template<typename Controller, typename Function>
auto make_app(const std::string& title, const Vec2& initial_size, View<Controller, Function>& initial_view){
  if (!glfwInit()){
    throw "GLFW error!\n";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  window = glfwCreateWindow(initial_size.x, initial_size.y, title.c_str(), nullptr, nullptr);

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height){
    gx::update_frame_buffer({ width + 0.f, height + 0.f });
  });
  
  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    throw "GLAD error!\n";
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  renderer::init();
  update_frame_buffer({ initial_size.x, initial_size.y });

  glfwShowWindow(window);

  gx::view_manager::current_view = &initial_view;
  gx::view_manager::run(window);

  glfwTerminate();
}

}; //namespace gx

