#pragma once

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Math.hpp"
#include "../Framework/Util/Util.hpp"
#include "../Framework/Font.hpp"

#include <glm/glm.hpp>

namespace gx::prop{

struct Position{
  Vec2 position;
};

struct Size{
  Vec2 size;
};

struct Color{
  glm::vec4 color;
};

struct Model{
  Mat4 model;
};

struct Label{
  std::string label;
};

struct FontFamily{
  Font* font;
};

struct RotationOffset{
  Vec2 rotation_offset;
};

struct Rotation{
  f32 rotation;
};

struct Img{
  Texture* texture;
};

struct TextureFilter{
  i32 min_filter;
  i32 mag_filter;
};

template<typename T>
struct State{
  T state;

  State(const T& t) : state(t) {}
};

constexpr auto Center(const Vec2& target_size, const Rect& parent){
  return Position{ parent.position + parent.size / 2 - target_size / 2 };
}

namespace colors{
  static constexpr auto White = glm::vec4(1, 1, 1, 1);
  static constexpr auto Black = glm::vec4(0, 0, 0, 1);
  static constexpr auto Red = glm::vec4(1, 0, 0, 1);
  static constexpr auto Green = glm::vec4(0, 1, 0, 1);
  static constexpr auto Blue = glm::vec4(0, 0, 1, 1);
  static constexpr auto Yellow = glm::vec4(1, 1, 0, 1);
  static constexpr auto Magenta = glm::vec4(1, 0, 1, 1);
  static constexpr auto Aqua = glm::vec4(0, 1, 1, 1);
}

} //namespace gx::prop

namespace gx{
  using namespace prop;
}
