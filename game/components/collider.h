#pragma once

#include "ecs/component.h"

namespace game::component {

struct Collider : public ecs::Component<Collider> {
    float radius = 1.f;
    int layer = -1;
};

} // namespace game::component