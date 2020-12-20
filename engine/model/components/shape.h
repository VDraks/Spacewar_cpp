#pragma once

#include "model/point.h"
#include "ecs/component.h"

namespace model::component {

struct Shape : public ecs::Component<Shape> {
    std::vector<Point> points;
};

} // namespace model::component


