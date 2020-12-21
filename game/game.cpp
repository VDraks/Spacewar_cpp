#include "game.h"

#include "collider_layer.h"
#include "game/components/collider.h"
#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "game/systems/bullet_controller_system.h"
#include "game/systems/physics/apply_forces_system.h"
#include "game/systems/physics/calculate_forces_system.h"
#include "game/systems/physics/collision_system.h"
#include "game/systems/world_boundary_system.h"
#include "game/components/star.h"
#include "model/components/shape.h"
#include "model/components/transform.h"
#include "systems/player_controller_system.h"

namespace game {

using namespace model::component;

namespace {

constexpr float startOffset = 80.f;

void addPlayer(Engine& engine, const component::Player& playerState, const Transform& transform) {
    auto& entityManager = engine.world().entityManager();
    const auto& ship = entityManager.createEntity();

    entityManager.addComponent<model::component::Transform>(ship) = transform;
    entityManager.addComponent<component::Player>(ship) = playerState;

    auto& shape = entityManager.addComponent<model::component::Shape>(ship);
    shape.points = {{-10.f, 10.f},
                    {-10.f, -10.f},
                    {20.f,  0.f}};

    entityManager.addComponent<component::RigidBody>(ship).mass = 3.0f;

    auto& collider = entityManager.addComponent<component::Collider>(ship);
    collider.radius = 10.f;
    collider.layer = playerState.layer;
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

    auto& collider = entityManager.addComponent<component::Collider>(star);
    collider.radius = 20.f;
    collider.layer = static_cast<int>(ColliderLayer::Star);
}

} // namespace


Game::Game() {
    component::Player firstPlayer;
    firstPlayer.rightKey = SDL_SCANCODE_D;
    firstPlayer.leftKey = SDL_SCANCODE_A;
    firstPlayer.fireKey = SDL_SCANCODE_W;
    firstPlayer.thrustKey = SDL_SCANCODE_S;
    firstPlayer.layer = static_cast<int>(ColliderLayer::FirstPlayer) ;

    Transform firstPlayerTransform;
    firstPlayerTransform.position = math::Vec2 { startOffset, _engine.world().worldSize().y - startOffset };
    firstPlayerTransform.angle = -(M_PI / 4);

    component::Player secondPlayer;
    secondPlayer.rightKey = SDL_SCANCODE_RIGHT;
    secondPlayer.leftKey = SDL_SCANCODE_LEFT;
    secondPlayer.fireKey = SDL_SCANCODE_UP;
    secondPlayer.thrustKey = SDL_SCANCODE_DOWN;
    firstPlayer.layer = static_cast<int>(ColliderLayer::SecondPlayer) ;

    Transform secondPlayerTransform;
    secondPlayerTransform.position = math::Vec2 { _engine.world().worldSize().x - startOffset, startOffset };
    secondPlayerTransform.angle = M_PI / 4 + M_PI / 2;


    addPlayer(_engine, firstPlayer, firstPlayerTransform);
    addPlayer(_engine, secondPlayer, secondPlayerTransform);

    initStar(_engine);

    _engine.addSystem<system::PlayerControllerSystem>(_engine.inputController());
    _engine.addSystem<system::CalculateForcesSystem>();
    _engine.addSystem<system::ApplyForcesSystem>();
    _engine.addSystem<system::CollisionSystem>();
    _engine.addSystem<system::BulletControllerSystem>();
    _engine.addSystem<system::WorldBoundarySystem>(_engine.world());
}

void Game::run() {
    _engine.run();
}

} // namespace game