#pragma once

#include "View.hpp"

namespace gx::view_manager{
  inline ViewBase* current_view;

  auto run(GLFWwindow* window) -> void;

  template<typename Controller, typename Function>
  inline auto switch_to(View<Controller, Function>& view){
    current_view->disabled = true;
    view.disabled = false;
    current_view = &view;
  }
}