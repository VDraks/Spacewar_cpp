#pragma once

#include "vec_2.h"

namespace math {

struct Utils {
    [[nodiscard]] static Vec2 angleVector(const float angle) {
        return { std::cos(angle), std::sin(angle) };
    }

    [[nodiscard]] static Vec2 rotatePoint(const Vec2& original, const float angle) {
        return { original.x * std::cos(angle) - original.y * std::sin(angle),
                 original.y * std::cos(angle) + original.x * std::sin(angle) };
    }

    [[nodiscard]] static Vec2 transformPoint(const Vec2& original, const float angle, const Vec2& offset) {
        return rotatePoint(original, angle) + offset;
    }

    [[nodiscard]] static float lerp(float v0, float v1, float t) {
        return v0 + t * (v1 - v0);
    }
};

} // namespace math

