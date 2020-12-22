#pragma once

#include "math/vec_2.h"
#include "ecs/entity_manager.h"

namespace model {

class World {
public:
    [[nodiscard]] const ecs::EntityManager& entityManager() const { return _entityManager; }
    [[nodiscard]] ecs::EntityManager& entityManager() { return _entityManager; }

    [[nodiscard]] const math::Vec2& worldSize() const { return _size; }

private:
    ecs::EntityManager _entityManager;
    math::Vec2 _size = { 1000.f, 1000.f };
};

inline math::Vec2 worldCenter(const World& world) {
    return { world.worldSize().x / 2.f, world.worldSize().y / 2.f };
}

} // namespace model