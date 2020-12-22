#include "player_controller_system.h"

#include <cmath>
#include <iostream>

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

    entityManager.addComponent<model::component::Transform>(entity) = transform;
}

} // namespace

PlayerControllerSystem::PlayerControllerSystem(const controller::InputController& inputController):
    _inputController(inputController) {

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
            if (player.lastBulletTime > component::Player::bulletTimeout) {
                spawners.emplace_back([t = transform, rb = rb, l = player.layer, &entityManager]() {
                    spawnBullet(entityManager, t, rb, l);
                });
                player.lastBulletTime = 0;
            }
        }

        if (_inputController.isPressed(player.thrustKey)) {
            rb.force = rb.force + math::Utils::angleVector(transform.angle) * shipForce;

            if (player.lastFuelParticleTime > component::Player::fuelParticleTimeout) {
                spawners.emplace_back([t = transform, &entityManager]() {
                    spawnFuelParticle(entityManager, t);
                });
                player.lastFuelParticleTime = 0;
            }
        }

        player.lastBulletTime += dt;
        player.lastFuelParticleTime += dt;
    }

    for (const auto& spawner : spawners) spawner();
}

} // namespace game::system