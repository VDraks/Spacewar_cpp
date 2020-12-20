#pragma once

#include "controller/input_controller.h"
#include "ecs/system.h"

namespace game::system {

class PlayerControllerSystem : public ecs::System {
public:
    explicit PlayerControllerSystem(const controller::InputController& inputController);

    void update(float dt, ecs::EntityManager& entityManager) override;

private:
    const controller::InputController& _inputController;
};

} // namespace game::system