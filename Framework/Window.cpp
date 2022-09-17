#include "Window.hpp"

#include "Util/Exception.hpp"

namespace window = gx::window;
using window::gl_window;

static bool glfw_initialised = false;

auto window::update_frame_buffer_(const gx::Vec2& size) -> void{
  window::size = size;

  gx::renderer::shader_program::set_uniform(
    "projection",
    glm::ortho(0.f, size.x, size.y, 0.f)
  );

  glViewport(0, 0, size.x, size.y);
}

auto window::init_gl() -> void{
  if (glfw_initialised){
    throw gx::GLException("GLFW already initialised!\n");
  }

  glfw_initialised = true;

  if (!glfwInit()){
    throw gx::GLException("GLFW error!\n");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  gl_window = glfwCreateWindow(100, 100, "", nullptr, nullptr);

  glfwSetFramebufferSizeCallback(gl_window, [](GLFWwindow*, int width, int height){
    update_frame_buffer_({ width + 0.f, height + 0.f });
  });
  
  glfwMakeContextCurrent(gl_window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    throw "GLAD error!\n";
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

auto window::set_title(const std::string& title) -> void{
  glfwSetWindowTitle(gl_window, title.c_str());
}

auto window::set_size(const Vec2& size) -> void{
  glfwSetWindowSize(gl_window, size.x, size.y);
}