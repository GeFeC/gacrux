#pragma once

#include <string>

namespace shaders{
  inline auto v_shader = R"(
    #version 330 core

    layout (location = 0) in vec2 position;
    layout (location = 1) in vec2 texture_position;

    uniform mat4 projection;
    uniform mat4 model;

    out vec2 f_texture_position;

    void main(){
      f_texture_position = texture_position;

      gl_Position = projection * model * vec4(position, 0.0, 1.0);
    }
  )";
};