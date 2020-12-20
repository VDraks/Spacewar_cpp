#pragma once

#include "math/vec_2.h"
#include "ecs/component.h"

namespace model::component {

struct Transform : public ecs::Component<Transform> {
    math::Vec2 position;
    float angle = 0.f;
};

} // namespace model::component


