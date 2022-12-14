#include "Text.hpp"

#include <algorithm>

using gx::Text;

Text::Text() {
  size = { 0.f, 0.f };

  color = glm::vec4(1, 1, 1, 1);
}

auto Text::set_font(Font* font) -> void{
  this->font = font;
  font_size = font->size;

  const auto i = std::max_element(font->glyphs.begin(), font->glyphs.end(), [](const auto& lhs, const auto& rhs){
    return lhs.bearing.y < rhs.bearing.y;
  });

  largest_glyph_bearing_y = i->bearing.y;
}

auto Text::set_text(const std::string& text)  -> void{
  this->text = text;
  glyphs.resize(text.size());

  for (size_t i = 0; i < text.size(); ++i){
    if (text[i] == '\n'){
      continue;
    }

    auto& current_font_glyph = font->glyphs[text[i]];

    glyphs[i] = create_glyph_from_char_(text[i]);
  }

  refresh();
}

auto Text::create_glyph_from_char_(char character) const  -> Glyph{
  auto new_text_glyph = Glyph{};
  auto& font_glyph = font->glyphs[character];

  new_text_glyph.size = round(font_glyph.size);

  if (character == ' '){
    new_text_glyph.size.x += font_glyph.advance >> 6;
  }

  new_text_glyph.bearing = font_glyph.bearing;
  new_text_glyph.advance = static_cast<i32>(font_glyph.advance);

  return new_text_glyph;
}

auto Text::refresh()  -> void{
  set_position(position);
  set_color(color);
}

auto Text::set_position(const Vec2& position)  -> void{
  set_position_for_every_glyph_(position);
  this->position = position;
}

static auto get_lines_count(const std::string& text){
  return (1 + std::count(text.begin(), text.end(), '\n'));
}

auto Text::set_position_for_every_glyph_(const Vec2& position)  -> void{
  auto y = position.y;
  auto x = position.x;

  for (i32 i = 0; i < glyphs.size(); ++i){
    auto& glyph = glyphs[i];

    if (text[i] == '\n'){
      x = position.x;
      y += font_size;

      glyph.position.x = x;
      glyph.position.y = y;
      continue;
    }

    const auto newglyph_position = Vec2(
      x + glyph.bearing.x,
      y - glyph.bearing.y + largest_glyph_bearing_y
    );

    glyph.position = round(newglyph_position);

    x += static_cast<f32>(glyph.advance >> 6);
  }

  size.x = get_text_width_();
  size.y = largest_glyph_bearing_y * get_lines_count(text);
}

auto Text::get_text_width_() -> f32{
  if (glyphs.size() == 0){
    return 0.f;
  }

  const auto lastglyph_x = glyphs.back().position.x;
  const auto last_glyph_width = glyphs.back().size.x;
  const auto first_glyph_x = glyphs.front().position.x;

  return lastglyph_x + last_glyph_width - first_glyph_x;
}

auto Text::set_color(const glm::vec4& color)  -> void{
  this->color = color;
  for (auto& glyph : glyphs){
    glyph.color = color;
  }
}

auto Text::get_color() const -> const glm::vec4&{
  return color;
}

auto Text::get_size() const -> const Vec2&{
  return size;
}

auto Text::get_position() const -> const Vec2{
  return position;
}

auto Text::get_text() const -> const std::string&{
  return text;
}

auto Text::get_glyph(i32 index) const -> const Glyph&{
  return glyphs[index];
}

auto Text::get_length() const -> i32{
  return glyphs.size();
}

auto Text::get_font() const -> Font*{
  return font;
}

auto Text::get_total_height() const -> f32{
  return get_lines_count(text) * font->size;
}

auto Text::get_line_number_at(i32 index) const -> i32{
  auto substring = text.substr(0, index + 1);
  return std::count(substring.begin(), substring.end(), '\n');
}
