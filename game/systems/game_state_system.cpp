#include "game_state_system.h"

#include "game/components/events/entities_collided.h"
#include "game/components/player.h"
#include "game/game_controller.h"

namespace game::system {

using namespace component::event;

GameStateSystem::GameStateSystem(GameController& gameController) :
        _gameController(gameController) {}

void GameStateSystem::update(float dt, ecs::EntityManager& entityManager) {

    std::vector<ecs::Entity> deadPlayers;
    for (const auto& [entity, components] : entityManager.getEntitySet<EntitiesCollided>()) {
        const auto& [collision] = components;

        for (const auto& collidedEntity : collision.entities) {
            if (entityManager.hasComponent<component::Player>(collidedEntity)) {
                deadPlayers.push_back(collidedEntity);
            }
        }
    }

    deadPlayers.erase(std::unique(deadPlayers.begin(), deadPlayers.end()), deadPlayers.end());

    if (!deadPlayers.empty()) {
        _gameController.setDeadPlayers(deadPlayers);
    }
}

} // namespace game::system