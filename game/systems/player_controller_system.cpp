#include "player_controller_system.h"

#include <cmath>
#include <iostream>

#include "game/components/bullet.h"
#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "math/angle_utils.h"
#include "model/components/shape.h"
#include "model/components/transform.h"

namespace game::system {

using namespace model::component;

namespace {

void spawnBullet(ecs::EntityManager& entityManager, const Transform& transform, const component::RigidBody& rb) {
    const auto& bulletEntity = entityManager.createEntity();
    auto& bulletTransform = entityManager.addComponent<Transform>(bulletEntity);
    const auto direction = math::AngleUtils::angleVector(transform.angle);
    bulletTransform.position = transform.position + direction * 20;

    auto& bullet = entityManager.addComponent<component::Bullet>(bulletEntity);
    bullet.velocity = rb.velocity + direction * 30;

    auto& shape = entityManager.addComponent<Shape>(bulletEntity);
    shape.points = { { 1.f,  1.f }, { 1.f, -1.f },
                     {-1.f, -1.f }, {-1.f,  1.f } };
}

} // namespace

PlayerControllerSystem::PlayerControllerSystem(const controller::InputController& inputController):
    _inputController(inputController) {

}

void PlayerControllerSystem::update(float dt, ecs::EntityManager& entityManager) {
    std::vector<std::function<void()>> spawners;

    for (auto [entity, components] : entityManager.getEntitySet<Transform, component::RigidBody, component::Player>()) {
        auto& [transform, rb, player] = components;

        const float angleSpeed = M_PI;
        const float speed = 30;

        if (_inputController.isPressed(player.leftKey)) {
            transform.angle -= angleSpeed * dt;
        }

        if (_inputController.isPressed(player.rightKey)) {
            transform.angle += angleSpeed * dt;
        }

        if (_inputController.isPressed(player.fireKey)) {
            if (player.lastBulletTime > component::Player::bulletTimeout) {
                spawners.emplace_back([t = transform, rb = rb, &entityManager]() {
                    spawnBullet(entityManager, t, rb);
                });
                player.lastBulletTime = 0;
            }
        }

        player.lastBulletTime += dt;

        if (_inputController.isPressed(player.thrustKey)) {
            rb.force = rb.force + math::AngleUtils::angleVector(transform.angle) * speed;
        }
    }

    for (const auto& spawner : spawners) spawner();
}

} // namespace game::system