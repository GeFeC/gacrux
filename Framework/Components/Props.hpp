#pragma once

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Math.hpp"
#include "../Framework/Font.hpp"

#include <glm/glm.hpp>

#define GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME, CONSTEXPR, EXTRA) struct CLASS{ \
  TYPE NAME{}; \
  EXTRA\
  template<typename T> \
  auto set_to(T& component) const{ \
    component.NAME = NAME; \
  }\
  CONSTEXPR CLASS() = default; \
  CONSTEXPR CLASS(TYPE&& NAME) : NAME(std::forward<TYPE>(NAME)) {} \
  template<typename... Ts> \
  CONSTEXPR CLASS(Ts&&... args) : NAME(std::forward<Ts>(args)...) {} \
}

#define GACRUX_MAKE_PROP(CLASS, TYPE, NAME) GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME, constexpr,)
#define GACRUX_MAKE_PROP_NON_CONST(CLASS, TYPE, NAME) GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME,,)

#define GACRUX_MAKE_COMPLEX_PROP(CLASS, TYPE, NAME, EXTRA) GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME, constexpr, EXTRA)
#define GACRUX_MAKE_COMPLEX_PROP_NON_CONST(CLASS, TYPE, NAME, EXTRA) GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME,, EXTRA)

namespace gx::prop{
  GACRUX_MAKE_PROP(Position, Vec2, position);
  GACRUX_MAKE_PROP(Size, Vec2, size);
  GACRUX_MAKE_PROP(Color, glm::vec4, color);
  GACRUX_MAKE_PROP(Rotation, f32, rotation);
  GACRUX_MAKE_PROP(RotationOffset, Vec2, rotation_offset);
  GACRUX_MAKE_PROP(Model, Mat4, model);
  GACRUX_MAKE_PROP(FontFamily, Font*, font);
  GACRUX_MAKE_PROP(Img, Texture*, texture);
  GACRUX_MAKE_PROP_NON_CONST(Label, std::string, label);

  //Complex props:
  struct Center{
    Vec2 position;
    Vec2 parent_pos, parent_size;

    constexpr Center() = default;
    constexpr Center(const Vec2& parent_pos, const Vec2& parent_size) : parent_pos(parent_pos), parent_size(parent_size) {}

    template<typename T>
    constexpr auto set_to(T& component) const{
      component.position = parent_pos + parent_size / 2 - Vec2(component.size) / 2;
    }
  };
}

namespace gx{
  using namespace prop;
}

namespace gx::colors{
  inline constexpr Color Red = Color(1, 0, 0, 1);
  inline constexpr Color Green = Color(0, 1, 0, 1);
  inline constexpr Color Blue = Color(0, 0, 1, 1);
  inline constexpr Color Yellow = Color(1, 1, 0, 1);
  inline constexpr Color Aqua = Color(0, 1, 1, 1);
  inline constexpr Color Magenta = Color(1, 0, 1, 1);
  inline constexpr Color Black = Color(0, 0, 0, 1);
  inline constexpr Color White = Color(1, 1, 1, 1);
}