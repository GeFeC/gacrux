#pragma once

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Math.hpp"
#include "../Framework/Renderer/Drawable/Text.hpp"
#include "../Framework/Font.hpp"

#include <glm/glm.hpp>

#define GACRUX_CREATE_PROP(NAME, PROP_TYPE, PROP_NAME) struct NAME{ \
  PROP_TYPE PROP_NAME; \
  NAME() = default; \
  NAME(PROP_TYPE PROP_NAME) : PROP_NAME(PROP_NAME) {} \
  template<typename T> \
  auto set_to(T& item) const{ \
    item.PROP_NAME = PROP_NAME; \
  } \
};

namespace gx::prop{
  struct Position{ 
    gx::Vec2 position;

    Position() = default;
    Position(gx::f32 x, gx::f32 y) : position{ x, y } {}

    template<typename T>
    auto set_to(T& item) const{
      item.position = position;
    }

    auto set_to(Text& text) const{
      text.set_position(position);
    }
  };

  struct Size{ 
    gx::Vec2 size;

    Size() = default;
    Size(gx::f32 x, gx::f32 y) : size{ x, y } {}

    template<typename T>
    auto set_to(T& item) const{
      item.size = size;
    }
  };

  struct Color{ 
    glm::vec4 color{};

    Color() = default;
    Color(gx::f32 r, gx::f32 g, gx::f32 b, gx::f32 a) : color{ r, g, b, a } {}

    template<typename T>
    auto set_to(T& item) const{
      item.color = color;
    }

    auto set_to(Text& text) const{
      text.set_color(color);
    }
  };

  struct Rotation{ 
    gx::f32 rotation;
    Rotation() = default;
    Rotation(gx::f32 angle) : rotation{ angle } {}

    template<typename T>
    auto set_to(T& item) const{
      item.rotation = rotation;
    }
  };

  struct RotationOffset{ 
    gx::Vec2 rotation_offset;

    RotationOffset() = default;
    RotationOffset(gx::f32 x, gx::f32 y) : rotation_offset{ x, y } {}

    template<typename T>
    auto set_to(T& item) const{
      item.rotation_offset = rotation_offset;
    }
  };

  struct Model{
    gx::Mat4 model;

    Model() = default;
    Model(const gx::Mat4& model) : model(model) {}

    template<typename T>
    auto set_to(T& item) const{
      item.model = model;
    }
  };

  struct FontFamily{
    Font* font;

    FontFamily() = default;
    FontFamily(Font& font) : font(&font) {}

    template<typename T>
    auto set_to(T& item) const{
      item.set_font(font);
    }
  };

  struct Label{
    std::string label;

    Label() = default;
    Label(const std::string& label) : label(label) {}

    template<typename T>
    auto set_to(T& item) const{
      item.label = label;
    }
  };


  struct Img{
    Texture* texture;

    Img() = default;
    Img(Texture& texture) : texture(&texture) {}

    template<typename T>
    auto set_to(T& item) const{
      item.texture = texture;
    }
  };
}

namespace gx{
  using namespace prop;
}