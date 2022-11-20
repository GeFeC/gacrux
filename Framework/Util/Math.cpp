#include "Math.hpp"

#include <algorithm>
#include <cmath>

using gx::Vec2;

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
