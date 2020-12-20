#include "bullet_controller_system.h"

#include "game/components/bullet.h."
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

void BulletControllerSystem::update(float dt, ecs::EntityManager& entityManager) {

    std::vector<ecs::Entity> toDestroy;

    for (auto [entity, components] : entityManager.getEntitySet<Transform, component::Bullet>()) {
        auto& [transform, bullet] = components;
        transform.position = transform.position + bullet.velocity * dt;

        bullet.currentLifeTime += dt;

        if (bullet.currentLifeTime > component::Bullet::lifeTime) toDestroy.push_back(entity);
    }

    for (const auto& entity : toDestroy) {
        entityManager.removeEntity(entity);
    }
}

} // namespace game::system