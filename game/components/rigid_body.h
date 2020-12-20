#pragma once

#include "ecs/component.h"
#include "math/vec_2.h"

namespace game::component {

struct RigidBody : public ecs::Component<RigidBody> {
    float mass = 10.f;
    math::Vec2 force;
    math::Vec2 velocity;
};

} // namespace game::component