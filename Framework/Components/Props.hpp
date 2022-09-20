#pragma once

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Math.hpp"
#include "../Framework/Font.hpp"

#include <glm/glm.hpp>

#define GACRUX_MAKE_PROP_HELPER(CLASS, TYPE, NAME, CONSTEXPR, INIT) struct CLASS{ \
  TYPE NAME{INIT}; \
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
  GACRUX_MAKE_PROP_HELPER(ColorBase, glm::vec4, color, constexpr, glm::vec4(1, 1, 1, 1));
  GACRUX_MAKE_PROP(Rotation, f32, rotation);
  GACRUX_MAKE_PROP(RotationOffset, Vec2, rotation_offset);
  GACRUX_MAKE_PROP(Model, Mat4, model);
  GACRUX_MAKE_PROP(FontFamily, Font*, font);
  GACRUX_MAKE_PROP(Img, Texture*, texture);
  GACRUX_MAKE_PROP_HELPER(TexMinFilter, int, min_filter, constexpr, GL_LINEAR_MIPMAP_LINEAR);
  GACRUX_MAKE_PROP_HELPER(TexMagFilter, int, mag_filter, constexpr, GL_LINEAR);
  GACRUX_MAKE_PROP_NON_CONST(Label, std::string, label);

  //Complex props:
  struct Color : ColorBase{
    constexpr Color() = default;
    constexpr Color(const glm::vec4& color) : ColorBase(color) {}

    template<typename... Ts>
    constexpr Color(Ts&&... args) : ColorBase(std::forward<Ts>(args)...) {}

    inline static constexpr ColorBase Red = ColorBase(1, 0, 0, 1);
    inline static constexpr ColorBase Green = ColorBase(0, 1, 0, 1);
    inline static constexpr ColorBase Blue = ColorBase(0, 0, 1, 1);
    inline static constexpr ColorBase Yellow = ColorBase(1, 1, 0, 1);
    inline static constexpr ColorBase Aqua = ColorBase(0, 1, 1, 1);
    inline static constexpr ColorBase Magenta = ColorBase(1, 0, 1, 1);
    inline static constexpr ColorBase Black = ColorBase(0, 0, 0, 1);
    inline static constexpr ColorBase White = ColorBase(1, 1, 1, 1);
  };

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

  struct CenterVertical{
    Vec2 position;
    f32 parent_y{}, parent_height{};

    constexpr CenterVertical() = default;
    constexpr CenterVertical(f32 y, f32 height) : parent_y(y), parent_height(height) {}

    template<typename T>
    constexpr auto set_to(T& component) const{
      component.position.y = parent_y + parent_height / 2 - Vec2(component.size).y / 2;
    }
  };

  struct CenterHorizontal{
    Vec2 position;
    f32 parent_x{}, parent_width{};

    constexpr CenterHorizontal() = default;
    constexpr CenterHorizontal(f32 x, f32 width) : parent_x(x), parent_width(width) {}

    template<typename T>
    constexpr auto set_to(T& component) const{
      component.position.x = parent_x + parent_width / 2 - Vec2(component.size).x / 2;
    }
  };
}

namespace gx{
  using namespace prop;
}