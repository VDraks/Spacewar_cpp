#include "collision_system.h"

#include <iostream>

#include "game/components/collider.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

void CollisionSystem::update(float dt, ecs::EntityManager& entityManager) {

    const auto& set = entityManager.getEntitySet<Transform, component::Collider>();
    for (auto itFirst = set.begin(); itFirst != set.end(); ++itFirst) {
        auto itSecond = itFirst;
        ++itSecond;
        for (; itSecond != set.end(); ++itSecond) {

            const auto& [t1, c1] = (*itFirst).second;
            const auto& [t2, c2] = (*itSecond).second;

            const float distance = (c1.radius + c2.radius);

            if ((t1.position - t2.position).squaredMagnitude() < distance * distance) {
                std::cout << "COLLISION" << std::endl;
            }

        }
    }
}

} // namespace game::system