#include "game.h"

#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "game/systems/bullet_controller_system.h"
#include "game/systems/physics/apply_forces_system.h"
#include "game/systems/physics/calculate_forces_system.h"
#include "game/components/star.h"
#include "model/components/shape.h"
#include "model/components/transform.h"
#include "systems/player_controller_system.h"

namespace game {

namespace {

void addPlayer(Engine& engine, const component::Player& playerState) {
    auto& entityManager = engine.world().entityManager();
    const auto& ship = entityManager.createEntity();
    entityManager.addComponent<model::component::Transform>(ship);
    auto& player = entityManager.addComponent<component::Player>(ship);
    player = playerState;

    auto& firstShipShape = entityManager.addComponent<model::component::Shape>(ship);
    firstShipShape.points = { {-10.f, 10.f }, {-10.f, -10.f }, {20.f, 0.f } };

    entityManager.addComponent<component::RigidBody>(ship);
}

void initStar(Engine& engine) {
    auto& entityManager = engine.world().entityManager();
    const auto& star = entityManager.createEntity();
    auto& transform = entityManager.addComponent<model::component::Transform>(star);
    transform.position = worldCenter(engine.world());

    auto& shape = entityManager.addComponent<model::component::Shape>(star);
    shape.points = { {0.f,  20.f }, { 5.f,  5.f }, { 20.f, 0.f }, { 5.f, -5.f },
                     {0.f, -20.f }, {-5.f, -5.f }, {-20.f, 0.f }, {-5.f,  5.f } };

    entityManager.addComponent<component::Star>(star);
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

    initStar(_engine);

    _engine.addSystem<system::PlayerControllerSystem>(_engine.inputController());
    _engine.addSystem<system::CalculateForcesSystem>();
    _engine.addSystem<system::ApplyForcesSystem>();
    _engine.addSystem<system::BulletControllerSystem>();
}

void Game::run() {
    _engine.run();
}

} // namespace game