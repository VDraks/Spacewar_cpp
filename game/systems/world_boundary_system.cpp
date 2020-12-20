#include "world_boundary_system.h"

#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

WorldBoundarySystem::WorldBoundarySystem(const model::World& world) : _world(world) {}

void WorldBoundarySystem::update(float dt, ecs::EntityManager& entityManager) {

    const auto size = _world.worldSize();

    for (auto [entity, components] : entityManager.getEntitySet<Transform>()) {
        auto& [transform] = components;


        while (transform.position.x > size.x) {
            transform.position.x -= size.x;
        }

        while (transform.position.x < 0) {
            transform.position.x += size.x;
        }

        while (transform.position.y > size.y) {
            transform.position.y -= size.y;
        }

        while (transform.position.y < 0) {
            transform.position.y += size.y;
        }
    }
}

} // namespace game::system