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

#define GACRUX_MAKE_MEMBER_PROXY(NAME, CLASS, TYPE, SETTER, GETTER) struct NAME{ \
  CLASS* owner; \
  NAME() = default; \
  auto assign_owner(CLASS* owner){ \
    this->owner = owner; \
  } \
  auto operator=(TYPE const& value){ \
    SETTER \
  } \
  operator TYPE(){ \
    GETTER \
  } \
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