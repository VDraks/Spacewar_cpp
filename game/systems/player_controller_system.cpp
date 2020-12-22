#include "player_controller_system.h"

#include <cmath>
#include <iostream>
#include <random>

#include "game/game_config.h"
#include "game/components/bullet.h"
#include "game/components/collider.h"
#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "math/utils.h"
#include "model/components/particle_system.h"
#include "model/components/shape.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

namespace {

constexpr float shipAngleSpeed = M_PI / 4;
constexpr float shipForce = 50;
constexpr float bulletSpeed = 70;

std::random_device randomDevice;

void spawnBullet(ecs::EntityManager& entityManager, const Transform& transform, const component::RigidBody& rb, const int layer) {
    const auto& entity = entityManager.createEntity();
    auto& bulletTransform = entityManager.addComponent<Transform>(entity);
    const auto direction = math::Utils::angleVector(transform.angle);
    bulletTransform.position = transform.position + direction * 20;

    auto& bullet = entityManager.addComponent<component::Bullet>(entity);
    bullet.velocity = rb.velocity + direction * bulletSpeed;

    auto& shape = entityManager.addComponent<Shape>(entity);
    shape.points = { { 1.f,  1.f }, { 1.f, -1.f },
                     {-1.f, -1.f }, {-1.f,  1.f } };
    shape.color = GameConfig::bulletColor;

    auto& collider = entityManager.addComponent<component::Collider>(entity);
    collider.radius = 1.f;
    collider.layer = layer;
}

void spawnFuelParticle(ecs::EntityManager& entityManager, const model::component::Transform& transform) {
    const auto entity = entityManager.createEntity();

    auto& particle = entityManager.addComponent<model::component::ParticleSystem>(entity);
    particle.settings.amount = 10;
    particle.settings.duration = 2.f;
    particle.shapeSettings.scaleStart = 0.01f;
    particle.shapeSettings.scaleEnd = 1.f;
    particle.shapeSettings.radius = 3.f;
    particle.shapeSettings.offset.x = -10.f;
    particle.settings.color = GameConfig::fuelColor;

    entityManager.addComponent<model::component::Transform>(entity) = transform;
}

} // namespace

PlayerControllerSystem::PlayerControllerSystem(const controller::InputController& inputController,
                                               const model::World& world) :
        _inputController(inputController), _world(world) {

}

void PlayerControllerSystem::update(float dt, ecs::EntityManager& entityManager) {
    std::vector<std::function<void()>> spawners;

    for (auto [entity, components] : entityManager.getEntitySet<Transform, component::RigidBody, component::Player>()) {
        auto& [transform, rb, player] = components;

        if (_inputController.isPressed(player.leftKey)) {
            transform.angle -= shipAngleSpeed * dt;
        }

        if (_inputController.isPressed(player.rightKey)) {
            transform.angle += shipAngleSpeed * dt;
        }

        if (_inputController.isPressed(player.fireKey)) {
            if (player.bulletCount > 0 && player.bulletCooldownTime > component::Player::bulletTimeout) {
                player.bulletCount--;
                spawners.emplace_back([t = transform, rb = rb, l = player.layer, &entityManager]() {
                    spawnBullet(entityManager, t, rb, l);
                });
                player.bulletCooldownTime = 0;
            }
        }

        if (_inputController.isPressed(player.thrustKey)) {
            if (player.fuelValue > 0) {
                player.fuelValue -= dt;
                rb.force = rb.force + math::Utils::angleVector(transform.angle) * shipForce;

                if (player.fuelParticleCooldownTime > component::Player::fuelParticleTimeout) {
                    spawners.emplace_back([t = transform, &entityManager]() {
                        spawnFuelParticle(entityManager, t);
                    });
                    player.fuelParticleCooldownTime = 0;
                }
            }
        }

        if (_inputController.isPressed(player.teleportationKey)) {
            if (player.teleportationCooldownTime > component::Player::teleportationTimeout) {
                std::uniform_real_distribution<float> distX(0, _world.worldSize().x);
                std::uniform_real_distribution<float> distY(0, _world.worldSize().y);
                transform.position.x = distX(randomDevice);
                transform.position.y = distY(randomDevice);
                player.teleportationCooldownTime = 0;
            }
        }

        player.bulletCooldownTime += dt;
        player.fuelParticleCooldownTime += dt;
        player.teleportationCooldownTime += dt;
    }

    for (const auto& spawner : spawners) spawner();
}

} // namespace game::system