#pragma once

#include "math/utils.h"
#include "math/vec_2.h"
#include "ecs/component.h"

namespace model::component {

struct Transform : public ecs::Component<Transform> {
    math::Vec2 position;
    float angle = 0.f;

    [[nodiscard]] math::Vec2 applyToPoint(const math::Vec2& point) const {
        return math::Utils::transformPoint(point, angle, position);
    }
};

} // namespace model::component


