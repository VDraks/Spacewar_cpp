#pragma once

#include "entity_manager.h"

namespace ecs {

class System {
public:
    virtual ~System() = default;

    virtual void update(float dt, EntityManager& entityManager) = 0;
};

} // namespace ecs