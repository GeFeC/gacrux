#include "Math.hpp"

#include <algorithm>
#include <cmath>

using gx::Vec2;

auto Vec2::operator==(const Vec2& other) const -> bool{
  return x == other.x && y == other.y;
}

auto Vec2::operator!=(const Vec2& other) const -> bool{
  return !(*this == other);
}

auto Vec2::operator+(const Vec2& other) const -> Vec2{
  return Vec2(x + other.x, y + other.y);
}

auto Vec2::operator-(const Vec2& other) const -> Vec2{
  return Vec2(x - other.x, y - other.y);
}

auto Vec2::operator+=(const Vec2& other) -> Vec2&{
  x += other.x;
  y += other.y;

  return *this;
}

auto Vec2::operator-=(const Vec2& other) -> Vec2&{
  x -= other.x;
  y -= other.y;

  return *this;
}

auto Vec2::operator-() const -> Vec2{
  return Vec2(-x, -y);
}

auto gx::max(const Vec2& lhs, const Vec2& rhs) -> Vec2{
  return Vec2(
    std::max(lhs.x, rhs.x),
    std::max(lhs.y, rhs.y)
  );
}

auto gx::round(const Vec2& lhs) -> Vec2{
  return Vec2(
    std::round(lhs.x),
    std::round(lhs.y)
  );
}