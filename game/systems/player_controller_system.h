#pragma once

#include "controller/input_controller.h"
#include "ecs/system.h"
#include "model/world.h"

namespace game::system {

class PlayerControllerSystem : public ecs::System {
public:
    explicit PlayerControllerSystem(const controller::InputController& inputController,
                                    const model::World& world);

    void update(float dt, ecs::EntityManager& entityManager) override;

private:
    const controller::InputController& _inputController;
    const model::World& _world;
};

} // namespace game::system