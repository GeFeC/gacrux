#pragma once

#include "../Framework/Util/Math.hpp"
#include "../Framework/Util/Util.hpp"
#include "Props.hpp"

#include <glm/glm.hpp>
#include <type_traits>

namespace gx{

template<typename... Props>
struct ComponentStyle : Props...{
  ComponentStyle() {}
  ComponentStyle(const Props&... props) : Props(props)... {}

  template<typename... ExtraProps>
  using with = ComponentStyle<Props..., ExtraProps...>;

  template<typename T>
  static constexpr auto contains_type = gx::has_type<T, Props...>;

  template<typename T>
  constexpr auto expect(const T& default_value = T()) const{
    if constexpr (contains_type<T>){
      return static_cast<T>(*this);
    }
    else{
      return default_value;
    }
  }
};

template<typename T, typename... Ts>
constexpr auto expect(const ComponentStyle<Ts...>& props){
  return props.template expect<T>();
}

using Component = ComponentStyle<Position, Size, Color>;
using Rotatable = Component::with<Rotation, RotationOffset>;
using Transformable = ComponentStyle<Model, Color>;
using TexturedComponent = Component::with<Img, TextureFilter>;

} //namespace gx
