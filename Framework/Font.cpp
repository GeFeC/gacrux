#include "Font.hpp"

#include "config.hpp"

using gx::Font;

Font::Font(const std::string& path) noexcept{
  this->source_path = config::FontsSrcPath + path;
}

auto Font::allocate(i32 font_size, u8 glyphs_count) -> void{
  this->size = font_size;

  FT_Library ft;
  if (FT_Init_FreeType(&ft)){
    throw FontException("Failed to initialise FT_Library!");
  }

  FT_Face face;
  if (FT_New_Face(ft, this->source_path.c_str(), 0, &face)){
    throw FontException("Failed to load font from: " + this->source_path);
  }

  FT_Set_Pixel_Sizes(face, 0, font_size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (u8 c = 0; c < glyphs_count; c++){
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
      throw FontException("Failed to load glyph: " + std::string{ static_cast<i8>(c) });
    }

    const auto texture_id = this->create_texture_from_face_(face);
    auto& current_glyph = this->glyphs.emplace_back();

    current_glyph.size = { face->glyph->bitmap.width, face->glyph->bitmap.rows };
    current_glyph.bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top };
    current_glyph.advance = face->glyph->advance.x;
    current_glyph.texture.id = texture_id;
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

auto Font::create_texture_from_face_(const FT_Face& face) noexcept -> GLuint{
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    face->glyph->bitmap.width,
    face->glyph->bitmap.rows,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    face->glyph->bitmap.buffer
  );

  glGenerateMipmap(GL_TEXTURE_2D);

  return texture_id;
}

auto Font::free() noexcept -> void{
  for (auto& glyph : this->glyphs){
    glyph.texture.free();
  }
}