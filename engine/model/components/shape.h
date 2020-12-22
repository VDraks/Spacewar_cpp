#pragma once

#include "math/vec_2.h"
#include "ecs/component.h"

namespace model::component {

struct Shape : public ecs::Component<Shape> {
    std::vector<math::Vec2> points;
};

} // namespace model::component


