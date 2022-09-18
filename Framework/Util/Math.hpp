#pragma once

#include "../aliases.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gx{
  struct Vec2{
    f32 x{}, y{};

    constexpr Vec2() = default;
    constexpr Vec2(f32 x, f32 y) : x(x), y(y) {}
    constexpr Vec2(f32 value) : Vec2(value, value) {}

    auto operator==(const Vec2& other) const -> bool;
    auto operator!=(const Vec2& other) const -> bool;

    auto operator+(const Vec2& other) const -> Vec2;
    auto operator-(const Vec2& other) const -> Vec2;

    auto operator+=(const Vec2& other) -> Vec2&;
    auto operator-=(const Vec2& other) -> Vec2&;

    auto operator-() const -> Vec2;

    constexpr auto operator*(f32 value) const{
      return Vec2(x * value, y * value);
    }
    constexpr auto operator/(f32 value) const{
      return Vec2(x / value, y / value);
    }
  };

  struct Mat4{
    glm::mat4 matrix;

    Mat4() : matrix(1.0f){}

    auto& translate(const Vec2& pos){
      matrix = glm::translate(matrix, glm::vec3(pos.x, pos.y, 0.f));
      return (*this);
    }

    auto& scale(const Vec2& size){
      matrix = glm::scale(matrix, glm::vec3(size.x, size.y, 0.f));
      return (*this);
    }

    auto& rotate(f32 degrees){
      matrix = glm::rotate(matrix, glm::radians(degrees), glm::vec3(0.f, 0.f, 1.f));
      return (*this);
    }
  };

  auto max(const Vec2& lhs, const Vec2& rhs) -> Vec2;
  auto round(const Vec2& lhs) -> Vec2;

  template<typename T>
  struct Interval{
    T min, max;
  };

  template<typename T>
  inline constexpr auto in_range(T min, T max){
    return Interval<T>{ min, max };
  }

  template<typename T>
  inline constexpr auto operator==(T value, const Interval<T>& interval){
    const auto [min, max] = interval;
    return value >= min && value <= max;
  }

  template<typename T>
  inline constexpr auto operator!=(T value, const Interval<T>& interval){
    return !(value == interval);
  }
};