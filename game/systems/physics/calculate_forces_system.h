#pragma once

#include "ecs/system.h"

namespace game::system {

class CalculateForcesSystem : public ecs::System {
public:
    void update(float dt, ecs::EntityManager& entityManager) override;
};

} // namespace game::system


