#pragma once

#include "model/world.h"
#include "ecs/system.h"

namespace game::system {

class WorldBoundarySystem : public ecs::System {
public:
    explicit WorldBoundarySystem(const model::World& world);

    void update(float dt, ecs::EntityManager& entityManager) override;

private:
    const model::World& _world;
};

} // namespace game::system

