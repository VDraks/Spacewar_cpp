#pragma once

#include "ecs/component.h"
#include "math/vec_2.h"

namespace game::component {

struct Star : public ecs::Component<Star> {
    float mass = 3000000.f;
};

} // namespace game::component