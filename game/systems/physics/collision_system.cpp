#include "collision_system.h"

#include <iostream>

#include "game/components/collider.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

void CollisionSystem::update(float dt, ecs::EntityManager& entityManager) {
    for (auto [firstEntity, firstComponents] : entityManager.getEntitySet<Transform, component::Collider>()) {
        for (auto [secondEntity, secondComponents] : entityManager.getEntitySet<Transform, component::Collider>()) {
            if (firstEntity == secondEntity) continue;

            const auto& [t1, c1] = firstComponents;
            const auto& [t2, c2] = secondComponents;

            const float distance = (c1.radius + c2.radius);

            if ((t1.position - t2.position).squaredMagnitude() < distance * distance) {
                std::cout << "COLLISION" << std::endl;
            }
        }
    }
}

} // namespace game::system