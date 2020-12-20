#include "bullet_controller_system.h"

#include "game/components/bullet.h."
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

void BulletControllerSystem::update(float dt, ecs::EntityManager& entityManager) {

    for (auto [entity, components] : entityManager.getEntitySet<Transform, component::Bullet>()) {
        auto& [transform, bullet] = components;
        transform.position = transform.position + bullet.velocity * dt;
    }
}

} // namespace game::system