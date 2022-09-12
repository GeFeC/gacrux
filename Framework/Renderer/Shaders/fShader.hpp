#pragma once

namespace shaders{
  inline auto f_shader = R"(
    #version 330 core

    in vec2 f_texture_position;

    uniform sampler2D pixel_map;
    uniform vec4 f_color;
    uniform int is_glyph = 0;

    uniform vec4 border_color;
    uniform int border_thickness = 0;

    out vec4 color;

    void main(){
      float alpha = texture(pixel_map, f_texture_position).r;

      color = f_color * (1 - is_glyph)
        + f_color * is_glyph * vec4(1.0, 1.0, 1.0, alpha);
    }
  )";
};