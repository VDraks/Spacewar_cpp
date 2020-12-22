#include "game.h"

#include "game/systems/bullet_controller_system.h"
#include "game/systems/game_state_system.h"
#include "game/systems/physics/apply_forces_system.h"
#include "game/systems/physics/calculate_forces_system.h"
#include "game/systems/physics/collision_system.h"
#include "game/systems/world_boundary_system.h"
#include "systems/player_controller_system.h"
#include "visualisers/ui_visualiser.h"

namespace game {

Game::Game():
        _gameController(_engine) {

    _gameController.startGame();

    _engine.addSystem<system::PlayerControllerSystem>(_engine.inputController());
    _engine.addSystem<system::CalculateForcesSystem>();
    _engine.addSystem<system::ApplyForcesSystem>();
    _engine.addSystem<system::CollisionSystem>();
    _engine.addSystem<system::BulletControllerSystem>();
    _engine.addSystem<system::WorldBoundarySystem>(_engine.world());
    _engine.addSystem<system::GameStateSystem>(_gameController);

    _engine.addVisualiser<visualiser::UiVisualiser>(_gameController);
}

void Game::run() {
    _engine.run();
}

} // namespace game