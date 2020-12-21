#include "collision_system.h"

#include "game/components/collider.h"
#include "game/components/events/entities_collided.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;
using namespace component::event;

void CollisionSystem::update(float dt, ecs::EntityManager& entityManager) {

    std::vector<ecs::Entity> toRemoveEvents;
    for (const auto& [entity, components] : entityManager.getEntitySet<EntitiesCollided>()) {
        toRemoveEvents.push_back(entity);
    }
    for (const auto& event : toRemoveEvents) {
        entityManager.removeEntity(event);
    }

    std::vector<EntitiesCollided::Pair> collisions;

    const auto& set = entityManager.getEntitySet<Transform, component::Collider>();
    for (auto itFirst = set.begin(); itFirst != set.end(); ++itFirst) {
        auto itSecond = itFirst;
        ++itSecond;
        for (; itSecond != set.end(); ++itSecond) {

            // TODO check layers

            const auto& [t1, c1] = (*itFirst).second;
            const auto& [t2, c2] = (*itSecond).second;

            const float distance = (c1.radius + c2.radius);

            if ((t1.position - t2.position).squaredMagnitude() < distance * distance) {
                collisions.push_back({ (*itFirst).first, (*itSecond).first });
            }

        }
    }

    for (const auto& collision : collisions) {
        auto event = entityManager.createEntity();
        entityManager.addComponent<EntitiesCollided>(event).entities = collision;
    }
}

} // namespace game::system