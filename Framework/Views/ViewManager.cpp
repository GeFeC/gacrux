#include "ViewManager.hpp"

auto gx::view_manager::run(GLFWwindow* window) -> void{
  while(!glfwWindowShouldClose(window)){
    (*current_view)(window);
  }
}