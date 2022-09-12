#pragma once

#include <vector>

#include "../Framework/aliases.hpp"
#include "../Framework/Font.hpp"

#include <GLFW/glfw3.h>

namespace gx{
  inline f32 delta_time = 0.f;

  struct ViewBase{
    bool disabled = false;
    virtual auto operator()(GLFWwindow* window) const -> void = 0;
  };

  using FontList = std::vector<std::pair<Font*, i32>>;

  template<typename Model, typename Controller, typename Function>
  struct View : ViewBase{
    Function render;
    FontList fonts;

    View(Function render, FontList fonts = FontList()) : render(render), fonts(fonts) {}

    auto operator()(GLFWwindow* window) const -> void override{
      Model model;

      for (auto& [font, size] : fonts){
        font->allocate(size);
      }

      Controller::setup(model);

      while(!disabled && !glfwWindowShouldClose(window)){
        const auto start_time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 0.f);

        Controller::loop(model);
        render(model);

        glfwPollEvents();
        glfwSwapBuffers(window);
        glfwSwapInterval(1);
        delta_time = glfwGetTime() - start_time;
      }

      for (auto& [font, size] : fonts){
        font->free();
      }
    }
  };

  template<typename Model, typename Controller, typename Function>
  auto make_view(Function render, FontList fonts = FontList()){
    return View<Model, Controller, Function>(render, fonts);
  }

  struct DummyModel{};
  struct DummyController{ 
    static auto setup(DummyModel) {}
    static auto loop(DummyModel) {}
  };

  template<typename Function>
  auto make_view(Function render, FontList fonts = FontList()){
    return View<DummyModel, DummyController, Function>(render, fonts);
  }
}