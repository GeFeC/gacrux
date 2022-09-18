#pragma once

#include "../Framework/Renderer/Renderer.hpp"
#include "Components.hpp"
#include "Text.hpp"

#include <utility>
#include <iostream>

namespace gx{

template<typename ComponentType>
struct ComponentRenderer{
  template<typename... Props>
  constexpr auto operator()(const Props&... props) const{
    ComponentType c;
    gx::set_props(c, props...);

    gx::renderer::draw(c);
  }
};

template<typename ComponentType>
inline ComponentRenderer<ComponentType> render_component;

inline auto component = render_component<Component>;
inline auto rotatable = render_component<Rotatable>;
inline auto transformable = render_component<Transformable>;
inline auto texture = render_component<TexturedComponent>;
inline auto text = render_component<Text>;

} //namespace gx