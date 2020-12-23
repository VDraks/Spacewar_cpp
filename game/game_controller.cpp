#include "game_controller.h"

#include "collider_layer.h"
#include "game_config.h"
#include "game/components/bullet.h"
#include "game/components/collider.h"
#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "game/components/star.h"
#include "model/components/particle_system.h"
#include "model/components/shape.h"
#include "model/components/transform.h"

namespace game {

using namespace model::component;

namespace {

constexpr float playerStartOffset = 80.f;

const std::vector<math::Vec2> firstShapePoints {
        {-12.f, 10.f},
        {-12.f, -10.f},
        {20.f,  0.f}
};

const std::vector<math::Vec2> secondShapePoints {
        {-12.f, 8.f}, {-2.f, 8.f}, {-2.f, 4.f},
        {16.f, 4.f}, {20.f, 0.f}, {16.f, -4.f},
        {-2.f, -4.f}, {-2.f, -8.f}, {-12.f, -8.f}
};

ecs::Entity addPlayer(Engine& engine, const component::Player& playerState,
                      const Transform& transform, const std::vector<math::Vec2>& shapePoints) {
    auto& entityManager = engine.world().entityManager();
    const auto& ship = entityManager.createEntity();

    entityManager.addComponent<model::component::Transform>(ship) = transform;
    entityManager.addComponent<component::Player>(ship) = playerState;

    auto& shape = entityManager.addComponent<model::component::Shape>(ship);
    shape.points = shapePoints;
    shape.color = GameConfig::shipColor;

    entityManager.addComponent<component::RigidBody>(ship).mass = 3.0f;

    auto& collider = entityManager.addComponent<component::Collider>(ship);
    collider.radius = 15.f;
    collider.layer = playerState.layer;

    return ship;
}

void addDeathParticle(ecs::EntityManager& entityManager, const ecs::Entity& playerEntity) {
    const auto entity = entityManager.createEntity();

    auto transform = entityManager.getComponent<model::component::Transform>(playerEntity);

    auto& particle = entityManager.addComponent<model::component::ParticleSystem>(entity);
    particle.settings.amount = 40;
    particle.settings.duration = 2.f;
    particle.shapeSettings.scaleStart = 0.01f;
    particle.shapeSettings.scaleEnd = 1.f;
    particle.shapeSettings.radius = 20.f;

    entityManager.addComponent<model::component::Transform>(entity) = transform;
}

void initStar(Engine& engine) {
    auto& entityManager = engine.world().entityManager();
    const auto& star = entityManager.createEntity();
    auto& transform = entityManager.addComponent<model::component::Transform>(star);
    transform.position = worldCenter(engine.world());

    auto& shape = entityManager.addComponent<model::component::Shape>(star);
    shape.points = { {0.f,  20.f }, { 5.f,  5.f }, { 20.f, 0.f }, { 5.f, -5.f },
                     {0.f, -20.f }, {-5.f, -5.f }, {-20.f, 0.f }, {-5.f,  5.f } };
    shape.color = GameConfig::starColor;

    entityManager.addComponent<component::Star>(star);

    auto& collider = entityManager.addComponent<component::Collider>(star);
    collider.radius = 20.f;
    collider.layer = static_cast<int>(ColliderLayer::Star);

    auto& particle = entityManager.addComponent<model::component::ParticleSystem>(star);
    particle.settings.amount = 40;
    particle.settings.loop = true;
    particle.settings.duration = 1.f;
    particle.shapeSettings.scaleEnd = 1.2f;
    particle.shapeSettings.radius = 20.f;
    particle.settings.color = GameConfig::starColor;
}

void cleanWorld(ecs::EntityManager& entityManager) {
    std::vector<ecs::Entity> toRemove;

    for (auto [entity, components] : entityManager.getEntitySet<component::Player>()) {
        toRemove.push_back(entity);
    }
    for (auto [entity, components] : entityManager.getEntitySet<component::Bullet>()) {
        toRemove.push_back(entity);
    }

    for (const auto& entity : toRemove) {
        entityManager.removeEntity(entity);
    }
}

} // namespace

GameController::GameController(Engine& engine) : _engine(engine) {

}

void GameController::startMatch() {
    auto& entityManager = _engine.world().entityManager();

    cleanWorld(entityManager);

    component::Player firstPlayer;
    firstPlayer.rightKey = SDL_SCANCODE_D;
    firstPlayer.leftKey = SDL_SCANCODE_A;
    firstPlayer.fireKey = SDL_SCANCODE_W;
    firstPlayer.thrustKey = SDL_SCANCODE_S;
    firstPlayer.teleportationKey = SDL_SCANCODE_Q;
    firstPlayer.layer = static_cast<int>(ColliderLayer::FirstPlayer) ;

    Transform firstPlayerTransform;
    firstPlayerTransform.position = math::Vec2 {playerStartOffset, _engine.world().worldSize().y - playerStartOffset };
    firstPlayerTransform.angle = -(static_cast<float>(M_PI) / 4);

    component::Player secondPlayer;
    secondPlayer.rightKey = SDL_SCANCODE_RIGHT;
    secondPlayer.leftKey = SDL_SCANCODE_LEFT;
    secondPlayer.fireKey = SDL_SCANCODE_UP;
    secondPlayer.thrustKey = SDL_SCANCODE_DOWN;
    secondPlayer.teleportationKey = SDL_SCANCODE_KP_ENTER;
    secondPlayer.layer = static_cast<int>(ColliderLayer::SecondPlayer) ;

    Transform secondPlayerTransform;
    secondPlayerTransform.position = math::Vec2 {_engine.world().worldSize().x - playerStartOffset, playerStartOffset };
    secondPlayerTransform.angle = static_cast<float>(M_PI) / 4 + static_cast<float>(M_PI) / 2;

    _players[0] = addPlayer(_engine, firstPlayer, firstPlayerTransform, firstShapePoints);
    _players[1] = addPlayer(_engine, secondPlayer, secondPlayerTransform, secondShapePoints);
}

void GameController::addScore(GameController::Player player) {
    _playerScores[static_cast<int>(player)]++;
}

void GameController::startGame() {
    initStar(_engine);

    startMatch();
}

void GameController::setDeadPlayers(const std::vector<ecs::Entity>& deadPlayers) {

    for (const auto player : deadPlayers) {
        if (player == _players[0]) addScore(Player::Second);
        if (player == _players[1]) addScore(Player::First);

        addDeathParticle(_engine.world().entityManager(), player);
    }

    if (!deadPlayers.empty()) {
        startMatch();
    }
}

} // namespace game