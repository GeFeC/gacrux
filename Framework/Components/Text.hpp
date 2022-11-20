#pragma once

#include "../Framework/Font.hpp"
#include "../Framework/aliases.hpp"
#include "./Components.hpp"
#include "../Framework/Util/Util.hpp"

#include <glm/glm.hpp>

#include <string>
#include <utility>
#include <cassert>
#include <vector>

namespace gx{

class Text{
private:
  struct Glyph :public Component{
    Vec2 bearing;
    i32 advance;
  };

  Vec2 position;
  Vec2 size;
  glm::vec4 color;
  Font* font;

  std::vector<Glyph> glyphs{};
  std::string text{};
  
  f32 largest_glyph_bearing_y{};
  f32 font_size{};

  auto set_position_for_every_glyph_(const Vec2& position) -> void;
  auto get_text_width_() -> f32;
  auto create_glyph_from_char_(char character) const -> Glyph;
  auto setup_text_height_() -> void;

public:
  Text();

  auto set_position(const Vec2& position) -> void;
  auto set_text(const std::string& text) -> void;
  auto set_color(const glm::vec4& color) -> void;
  auto set_font(Font* font) -> void;

  auto refresh() -> void;

  auto get_color() const -> const glm::vec4&;
  auto get_size() const -> const Vec2&;
  auto get_position() const -> const Vec2;
  auto get_text() const -> const std::string&;
  auto get_font() const -> Font*;

  auto get_glyph(i32 index) const -> const Glyph&;
  auto get_length() const -> i32;

  /*
    The difference between this and Text::get_size().y is that
    Text::get_size().y returns something called 'bearingY' and
    this function returns 'real' height
  */
  auto get_total_height() const -> f32;

  auto get_line_number_at(i32 index) const -> i32;

  static auto get_component_size(const std::string& label, Font* font = Font::current){
    auto component = Text{};
    component.set_font(font);
    component.set_text(label);

    return component.get_size();
  }
};

}//namespace gx
