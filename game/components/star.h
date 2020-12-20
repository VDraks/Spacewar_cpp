#pragma once

#include "ecs/component.h"
#include "math/vec_2.h"

namespace game::component {

struct Star : public ecs::Component<Star> {
    float mass = 1000000.f;
};

} // namespace game::component