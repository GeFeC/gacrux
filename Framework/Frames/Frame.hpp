#pragma once

#include <vector>

#include "../Framework/aliases.hpp"
#include "../Framework/Font.hpp"
#include "../Framework/Window.hpp"
#include "Resources.hpp"

#include <GLFW/glfw3.h>

namespace gx{
  inline f32 delta_time = 0.f;
  inline bool should_switch_frame = false;

  struct DummyState{};
  struct DummyController{
    template<typename T>
    auto operator()(T&) const {}
  };

  template<typename State = DummyState, typename Controller = DummyController, typename Function>
  auto make_frame(Function render, Resources resources = Resources(), Controller controller = DummyController()){
    return [render = std::move(render), controller = std::move(controller), resources = std::move(resources)]{
      for (auto [font, size] : resources.fonts){
        font->allocate(size);
      }

      for (auto texture : resources.textures){
        texture->allocate();
      }

      auto state = State{};

      while(!should_switch_frame && !glfwWindowShouldClose(gx::window::gl_window)){
        const auto start_time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 0.f);

        controller(state);
        render(state);

        glfwPollEvents();
        glfwSwapBuffers(gx::window::gl_window);
        glfwSwapInterval(1);
        delta_time = glfwGetTime() - start_time;
      }

      for (auto& [font, size] : resources.fonts){
        font->free();
      }
      for (auto texture : resources.textures){
        texture->free();
      }
    };
  }
}
