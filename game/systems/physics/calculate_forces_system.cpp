#include "calculate_forces_system.h"

#include "game/components/rigid_body.h"
#include "game/components/star.h"
#include "model/components/transform.h"

namespace game::system {

namespace {
    constexpr float G = 6.67430f; // ·10−11
}

using namespace model::component;

void CalculateForcesSystem::update(float dt, ecs::EntityManager& entityManager) {

    for (auto [starEntity, starComponents] : entityManager.getEntitySet<Transform, component::Star>()) {

        const auto& [starTransform, star] = starComponents;

        for (auto [entity, components] : entityManager.getEntitySet<Transform, component::RigidBody>()) {
            auto& [transform, rb] = components;

            const math::Vec2 direction = starTransform.position - transform.position;
            const float squaredR = direction.squaredMagnitude();
            const float f = rb.mass * star.mass / squaredR;

            rb.force = rb.force + direction.getNormalized() * f;
        }
    }
}

} // namespace game::system