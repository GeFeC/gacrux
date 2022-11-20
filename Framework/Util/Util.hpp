#pragma once

#define NDEBUG

#include "Math.hpp"
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
  struct Rect{
    Vec2 position;
    Vec2 size;
  };

  template<typename T>
  using type_of = std::remove_const_t<std::remove_reference_t<T>>;

  template<typename Target, typename T, typename... Ts>
  static constexpr auto has_type = std::is_same_v<Target, T> || has_type<Target, Ts...>;

  template<typename Target, typename T>
  static constexpr auto has_type<Target, T> = std::is_same_v<Target, T>;

  inline i32 i = 0;

  inline auto get_file_content(const std::string& filePath) -> std::string;

  inline auto rng = std::mt19937{ static_cast<std::mt19937::result_type>(std::time(0)) };

  template<typename T>
  inline auto get_random_value(T min, T max){
    auto engine = std::uniform_int_distribution<T>{ min, max };
    return engine(rng);
  }

  template<typename Fun>
  inline auto loop(i32 count, const Fun& fun){
    gx::i = 0;
    for (i32 i = 0; i < count; ++i){
      fun();
      ++gx::i;
    }
  }
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
