#pragma once

#include <random>

#include "ecs/system.h"
#include "math/vec_2.h"

namespace model::system {

class ParticleSystem : public ecs::System {
public:
    void update(float dt, ecs::EntityManager& entityManager) override;
private:
    std::random_device _randomDevice;

    [[nodiscard]] float randomRange(float min, float max);
    [[nodiscard]] math::Vec2 generatePoint(float radius);
};

} // namespace model::system


