#include "Texture.hpp"

#include "Util/Exception.hpp"

#include "config.hpp"

#include <fstream>
#include <vector>

using gx::Texture;

Texture::Texture(const std::string& path) noexcept{
  this->source_path = gx::config::TexturesSrcPath + path;
}

auto Texture::allocate() -> void{
  this->generate_();
}

auto Texture::generate_() noexcept -> void{
  glGenTextures(1, &this->id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->id);
}

auto Texture::set_min_filter(i32 min_filter) const noexcept -> void{
  glBindTexture(GL_TEXTURE_2D, this->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
}

auto Texture::set_mag_filter(i32 mag_filter) const noexcept -> void{
  glBindTexture(GL_TEXTURE_2D, this->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

auto Texture::bind() const noexcept -> void{
  glBindTexture(GL_TEXTURE_2D, this->id);
}

auto Texture::free() noexcept -> void{
  glDeleteTextures(1, &this->id);
}