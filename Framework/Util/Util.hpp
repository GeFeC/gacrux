#pragma once

#define NDEBUG

#include "Exception.hpp"
#include "../aliases.hpp"

#include <sstream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include <type_traits>
#include <algorithm>

namespace gx{
  inline auto rng = std::mt19937{ static_cast<std::mt19937::result_type>(std::time(0)) };

  inline auto get_file_content(const std::string& filePath) -> std::string;

  template<typename T, typename std::enable_if_t<std::is_integral_v<T>>>
  inline auto from_string(const std::string& string) noexcept -> T{
    try{
      return static_cast<T>(std::stol(string));
    }
    catch(const std::invalid_argument&){
      return 0;
    }
  }

  template<typename T>
  inline auto get_random_value(T min, T max) noexcept{
    auto engine = std::uniform_int_distribution<T>{ min, max };
    return engine(rng);
  }

  struct Direction{
    i32 horizontal, vertical;
  };
}

#ifdef NDEBUG

#include "../Framework/Util/Math.hpp"

inline auto& operator<<(std::ostream& out, const gx::Vec2& vec2){
  return out << "[" << vec2.x << " : " << vec2.y << "]\n";
}

template<typename T1, typename T2>
inline auto& operator<<(std::ostream& out, const std::pair<T1, T2>& pair){
  return out << "[" << pair.first << " : " << pair.second << "]\n";
}

#endif