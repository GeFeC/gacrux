#include "Shader.hpp"

#include "../Framework/aliases.hpp"
#include "../Framework/Util/Exception.hpp"

#include <array>
#include <vector>
#include <string>

using gx::Shader;

auto Shader::create(ShaderType type, String_t& script) -> void{
  shader_id = glCreateShader(static_cast<i32>(type)); 
  glShaderSource(shader_id, 1, &script, nullptr);
  
  compile();
}

auto Shader::compile() -> void{
  glCompileShader(shader_id);

  auto success = i32{};
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
  if (success) {
    return;
  }

  static constexpr auto ERROR_MESSAGE_BUFFER_SIZE = 512;

  auto msg = std::array<char, ERROR_MESSAGE_BUFFER_SIZE>{};
  glGetShaderInfoLog(shader_id, ERROR_MESSAGE_BUFFER_SIZE, NULL, msg.data());
  
  throw ShaderException("Failed to compile shader with error:\n" + std::string{ msg.data() });
}
