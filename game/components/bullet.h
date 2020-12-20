#pragma once

#include "ecs/component.h"
#include "math/vec_2.h"

namespace game::component {

struct Bullet : public ecs::Component<Bullet> {
    math::Vec2 velocity;
};

} // namespace game::component