#pragma once

#include "../Framework/Renderer/Renderer.hpp"
#include "../Framework/Util/Math.hpp"

#include <glm/glm.hpp>

namespace gx{
  template<typename Component>
  constexpr auto set_props(Component& component){}

  template<typename Component, typename P, typename... Props>
  constexpr auto set_props(Component& component, const P& p, const Props&... props){
    p.set_to(component);
    set_props(component, props...);
  }

  template<typename Component, typename... Props>
  auto render_component(const Props&... props){
    Component c;
    gx::set_props(c, props...);

    gx::renderer::draw(c);
  }
}

namespace gx{
  template<typename... Props>
  auto component(const Props&... props){
    render_component<Component>(props...);
  }

  template<typename... Props>
  auto rotatable(const Props&... props){
    render_component<Rotatable>(props...);
  }

  template<typename... Props>
  auto transformable(const Props&... props){
    render_component<Transformable>(props...);
  }

  template<typename... Props>
  auto text(const std::string& label, const Props&... props){
    Text text;
    gx::set_props(text, props...);
    text.set_text(label);

    gx::renderer::draw(text);
  }
}

#include "CustomComponents.hpp"