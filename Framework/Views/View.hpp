#pragma once

#include <vector>

#include "../Framework/aliases.hpp"
#include "../Framework/Font.hpp"
#include "Resources.hpp"

#include <GLFW/glfw3.h>

namespace gx{
  inline f32 delta_time = 0.f;

  struct ViewBase{
    bool disabled = false;
    virtual auto operator()(GLFWwindow* window) const -> void = 0;
  };

  

  template<typename Controller, typename Function>
  struct View : ViewBase{
    Function render;
    Resources resources;

    View(Function render, Resources resources = Resources()) : render(render), resources(resources) {}

    auto operator()(GLFWwindow* window) const -> void override{
      for (auto [font, size] : resources.fonts){
        font->allocate(size);
      }
      for (auto texture : resources.textures){
        texture->allocate();
      }

      Controller::setup();

      while(!disabled && !glfwWindowShouldClose(window)){
        const auto start_time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 0.f);

        Controller::loop();
        render();

        glfwPollEvents();
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        delta_time = glfwGetTime() - start_time;
      }

      for (auto& [font, size] : resources.fonts){
        font->free();
      }
      for (auto texture : resources.textures){
        texture->free();
      }
    }
  };

  struct DummyController{ 
    static auto setup() {}
    static auto loop() {}
  };

  template<typename Controller = DummyController, typename Function>
  auto make_view(Function render, Resources resources = Resources()){
    return View<Controller, Function>(render, resources);
  }
}