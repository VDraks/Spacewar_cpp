#include "player_controller_system.h"

#include <cmath>
#include <iostream>
#include <math/angle_utils.h>

#include "game/components/player.h"
#include "game/components/rigid_body.h"
#include "model/components/transform.h"

namespace game::system {

PlayerControllerSystem::PlayerControllerSystem(const controller::InputController& inputController):
    _inputController(inputController) {

}

void PlayerControllerSystem::update(float dt, ecs::EntityManager& entityManager) {
    for (auto [entity, components] : entityManager.getEntitySet<model::component::Transform, component::RigidBody, component::Player>()) {
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
//            transform.position.x += speed * dt;
        }

        if (_inputController.isPressed(player.thrustKey)) {
            rb.force = rb.force + math::AngleUtils::angleVector(transform.angle) * speed;
//            transform.position.x -= speed * dt;
        }
    }
}

} // namespace game::system