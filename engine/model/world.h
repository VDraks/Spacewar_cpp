#pragma once

#include "game_object.h"

#include "ecs/entity_manager.h"

namespace model {

class World {
public:
    [[nodiscard]] const ecs::EntityManager& entityManager() const { return _entityManager; }
    [[nodiscard]] ecs::EntityManager& entityManager() { return _entityManager; }

private:
    ecs::EntityManager _entityManager;
};

} // namespace model