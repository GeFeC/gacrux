#include "Util.hpp"

inline auto gx::get_file_content(const std::string& filePath) -> std::string{
  auto file = std::ifstream(filePath, std::ios::in);

  if (!file.good()){
    throw FileException("Failed to load file from: " + filePath);
  }

  auto ss = std::ostringstream{};
  ss << file.rdbuf();

  return ss.str();
}