#pragma once

#include <cmath>

namespace math {

struct Vec2 {
    float x = 0.f;
    float y = 0.f;

    [[nodiscard]] Vec2 operator + (const Vec2& rhs) const {
        return { x + rhs.x, y + rhs.y };
    }

    [[nodiscard]] Vec2 operator - (const Vec2& rhs) const {
        return { x - rhs.x, y - rhs.y };
    }

    [[nodiscard]] Vec2 operator * (const float& rhs) const {
        return { x * rhs, y * rhs };
    }

    [[nodiscard]] float magnitude() const {
        return sqrtf(squaredMagnitude());
    }

    [[nodiscard]] float squaredMagnitude() const {
        return x * x + y * y;
    }

    [[nodiscard]] Vec2 getNormalized() const {
        const auto m = magnitude();
        if (m == 0) return { 0.f, 0.f };
        return { x / m, y / m };
    }
};

} // namespace math


