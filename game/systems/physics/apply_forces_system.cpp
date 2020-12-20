#include "apply_forces_system.h"

#include "game/components/rigid_body.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

void ApplyForcesSystem::update(float dt, ecs::EntityManager& entityManager) {

    for (auto [entity, components] : entityManager.getEntitySet<Transform, component::RigidBody>()) {
        auto& [transform, rb] = components;

        const math::Vec2 a = rb.force * (1.f / rb.mass);
        rb.velocity = rb.velocity + a * dt;
        rb.force = {};

        transform.position = transform.position + rb.velocity * dt;
    }
}

} // namespace game::system