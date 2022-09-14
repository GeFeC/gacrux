#include "Texture.hpp"

#include "Util/Exception.hpp"

#include "config.hpp"

#include <fstream>
#include <vector>
#include <stb/stb_image.h>

using gx::Texture;

Texture::Texture(const std::string& path) noexcept{
  this->source_path = gx::config::TexturesSrcPath + path;
}

auto Texture::allocate() -> void{
  glGenTextures(1, &id);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, id);

  //Load texture from file
  {
    i32 width, height, channels;
    auto image_buffer = stbi_load(source_path.c_str(), &width, &height, &channels, 0);

    if (image_buffer == nullptr) {
      throw TextureException("Failed to load image from: " + source_path);
    }
      
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(
      GL_TEXTURE_2D, 
      0, 
      GL_RGBA, 
      width, 
      height, 
      0, 
      GL_RGBA, 
      GL_UNSIGNED_BYTE, 
      image_buffer
    );
    
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_buffer);
  }
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