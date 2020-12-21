#include <game/components/player.h>
#include "game_state_system.h"

#include "game/components/events/entities_collided.h"
#include "game/game_controller.h"

namespace game::system {

using namespace component::event;

GameStateSystem::GameStateSystem(GameController& gameController) :
        _gameController(gameController) {}

void GameStateSystem::update(float dt, ecs::EntityManager& entityManager) {

    std::array<bool, 2> playerIsDead = { false, false };
    for (const auto& [entity, components] : entityManager.getEntitySet<EntitiesCollided>()) {

        const auto& [collision] = components;

        for (const auto& collidedEntity : collision.entities) {
            if (entityManager.hasComponent<component::Player>(collidedEntity)) {
                const auto& player = entityManager.getComponent<component::Player>(collidedEntity);
                playerIsDead.at(player.layer) = true;
            }
        }
    }

    if (playerIsDead[0]) _gameController.addScore(GameController::Player::Second);
    if (playerIsDead[1]) _gameController.addScore(GameController::Player::First);

    if (playerIsDead[0] || playerIsDead[1]) {
        _gameController.startMatch();
    }
}

} // namespace game::system