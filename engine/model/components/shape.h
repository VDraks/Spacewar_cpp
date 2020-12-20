#pragma once

#include "math/point.h"
#include "ecs/component.h"

namespace model::component {

struct Shape : public ecs::Component<Shape> {
    std::vector<math::Point> points;
};

} // namespace model::component


