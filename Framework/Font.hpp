#pragma once

#include "Util/Exception.hpp"
#include "Texture.hpp"

#include "Util/Math.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <vector>

namespace gx{

class Font{
private:
  struct Glyph{
    Texture texture;
    gx::Vec2 size;
    gx::Vec2 bearing;
    i32 advance;
  };

  std::string source_path{};
  auto create_texture_from_face_(const FT_Face& face) noexcept -> GLuint;

public:
  i32 size{};

  std::vector<Glyph> glyphs;

  Font(const std::string& path) noexcept;

  auto allocate(i32 font_size, u8 glyphs_count = 128) -> void;
  auto free() noexcept -> void;
};

}