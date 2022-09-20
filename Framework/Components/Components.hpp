#pragma once

#include "../Framework/Util/Math.hpp"
#include "../Framework/Util/Util.hpp"
#include "./CustomComponents.hpp"
#include "Props.hpp"

#include <glm/glm.hpp>
#include <type_traits>

namespace gx{

template<typename ComponentType>
constexpr auto set_props(ComponentType& component){}

template<typename ComponentType, typename P, typename... Props>
constexpr auto set_props(ComponentType& component, const P& p, const Props&... props){
  p.set_to(component);
  set_props(component, props...);
}

using Component = ComponentStyle<Position, Size, Color>;
using Rotatable = Component::with<Rotation, RotationOffset>;
using Transformable = ComponentStyle<Model, Color>;
using TexturedComponent = Component::with<Img, TexMinFilter, TexMagFilter>;

} //namespace gx