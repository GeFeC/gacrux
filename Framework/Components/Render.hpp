#pragma once

#include "../Framework/Renderer/Renderer.hpp"
#include "Components.hpp"
#include "Text.hpp"

#include <utility>
#include <iostream>

namespace gx{
inline auto component = [](const auto& props){
  auto component = Component{};

  component.position = props.template expect<Position>().position;
  component.size = props.template expect<Size>().size;
  component.color = props.template expect<Color>().color;

  renderer::draw(component);
};

inline auto rotatable = [](const auto& props){
  auto component = Rotatable{};

  component.position = props.template expect<Position>().position;
  component.size = props.template expect<Size>().size;
  component.color = props.template expect<Color>().color;
  component.rotation = props.template expect<Rotation>().rotation;
  component.rotation_offset = props.template expect<RotationOffset>().rotation_offset;

  renderer::draw(component);
};

inline auto texture = [](const auto& props){
  auto component = TexturedComponent{};

  component.position = props.template expect<Position>().position;
  component.size = props.template expect<Size>().size;
  component.color = props.template expect<Color>().color;
  component.texture = props.template expect<Img>().texture;

  renderer::draw(component);
};

inline auto text = [](const auto& props){
  auto component = Text{};

  component.set_font(props.template expect<FontFamily>(FontFamily{gx::Font::current}).font);
  component.set_position(props.template expect<Position>().position);
  component.set_color(props.template expect<Color>().color);
  component.set_text(props.template expect<Label>().label);

  renderer::draw(component);
};

inline auto transformable = [](const auto& props){
  auto component = Transformable{};
  
  component.model = props.template expect<Model>().model;
  component.color = props.template expect<Color>().color;

  renderer::draw(component);
};

namespace render{

template<typename Callable, typename = std::enable_if_t<std::is_class_v<Callable>>>
auto operator++(const Callable& callable, int){
  return [&callable = callable](const auto&... args){
    callable(ComponentStyle<gx::type_of<decltype(args)>...>{ args... });
  };
}

} //namespace render

} //namespace gx
