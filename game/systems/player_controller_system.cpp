#include "player_controller_system.h"

#include <math.h>
#include <iostream>

#include "game/components/player.h"
#include "model/components/transform.h"

namespace game::system {

PlayerControllerSystem::PlayerControllerSystem(const controller::InputController& inputController):
    _inputController(inputController) {

}

void PlayerControllerSystem::update(float dt, ecs::EntityManager& entityManager) {
    for (auto [entity, components] : entityManager.getEntitySet<model::component::Transform, component::Player>()) {
        auto& [transform, player] = components;

        const float angleSpeed = M_PI / 1000.f;
        const float speed = 30 / 1000.f;

        if (_inputController.isPressed(player.leftKey)) {
            transform.angle += angleSpeed * dt;

        }

        if (_inputController.isPressed(player.rightKey)) {
            transform.angle -= angleSpeed * dt;
        }

        if (_inputController.isPressed(player.fireKey)) {
            transform.position.x += speed * dt;
        }

        if (_inputController.isPressed(player.thrustKey)) {
            transform.position.x -= speed * dt;
        }
    }
}

} // namespace game::system