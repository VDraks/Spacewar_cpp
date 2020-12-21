#pragma once

#include "ecs/system.h"

namespace game { class GameController; }

namespace game::system {

class GameStateSystem : public ecs::System {
public:
    explicit GameStateSystem(GameController& gameController);

    void update(float dt, ecs::EntityManager& entityManager) override;

private:
    GameController& _gameController;
};

} // namespace game::system

