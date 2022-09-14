#pragma once

#include <vector>

#include "../Font.hpp"
#include "../Texture.hpp"
#include "../aliases.hpp"

namespace gx{
  using FontList = std::vector<std::pair<Font*, i32>>;
  using TextureList = std::vector<Texture*>;

  struct Resources{
    FontList fonts;
    TextureList textures;

    Resources() = default;
    Resources(const FontList& fonts, const TextureList& textures) : fonts(fonts), textures(textures) {}
  };

}; //namespace gx