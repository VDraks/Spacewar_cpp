#pragma once

#include "vec_2.h"

namespace math {

struct AngleUtils {
    static Vec2 angleVector(float angle) {
        return { std::cos(angle), std::sin(angle) };
    }

};

} // namespace math

