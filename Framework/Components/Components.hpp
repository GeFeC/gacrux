#pragma once

#include "../Framework/Renderer/Renderer.hpp"
#include "../Framework/Util/Math.hpp"

#include <glm/glm.hpp>

namespace gx{
  template<typename ComponentType>
  constexpr auto set_props(ComponentType& component){}

  template<typename ComponentType, typename P, typename... Props>
  constexpr auto set_props(ComponentType& component, const P& p, const Props&... props){
    p.set_to(component);
    set_props(component, props...);
  }

  template<typename ComponentType, typename... Props>
  auto render_component(const Props&... props){
    ComponentType c;
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
  auto texture(const Props&... props){
    render_component<TexturedComponent>(props...);
  }

  template<typename... Props>
  auto text(const Props&... props){
    render_component<Text>(props...);
  }
}

#include "CustomComponents.hpp"