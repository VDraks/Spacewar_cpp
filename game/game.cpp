#include "game.h"

#include "game/components/player.h"
#include "model/components/shape.h"
#include "model/components/transform.h"
#include "systems/player_controller_system.h"

namespace game {

namespace {

void addPlayer(Engine& engine, const component::Player& playerState) {
    auto& entityManager = engine.world().entityManager();
    const auto& firstShip = entityManager.createEntity();
    entityManager.addComponent<model::component::Transform>(firstShip);
    auto& player = entityManager.addComponent<component::Player>(firstShip);
    player = playerState;

    auto& firstShipShape = entityManager.addComponent<model::component::Shape>(firstShip);
    firstShipShape.points = { {-10.f, 0.f }, {10.f, 0.f }, {0.f, 30.f } };
}

} // namespace


Game::Game() {
    component::Player firstPlayer;
    firstPlayer.rightKey = SDL_SCANCODE_D;
    firstPlayer.leftKey = SDL_SCANCODE_A;
    firstPlayer.fireKey = SDL_SCANCODE_W;
    firstPlayer.thrustKey = SDL_SCANCODE_S;

    component::Player secondPlayer;
    secondPlayer.rightKey = SDL_SCANCODE_RIGHT;
    secondPlayer.leftKey = SDL_SCANCODE_LEFT;
    secondPlayer.fireKey = SDL_SCANCODE_UP;
    secondPlayer.thrustKey = SDL_SCANCODE_DOWN;

    addPlayer(_engine, firstPlayer);
    addPlayer(_engine, secondPlayer);

    _engine.addSystem<system::PlayerControllerSystem>(_engine.inputController());
}

void Game::run() {
    _engine.run();
}

} // namespace game