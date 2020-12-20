#pragma once

#include <SDL2/SDL.h>

#include "ecs/component.h"

namespace game::component {

struct Player : public ecs::Component<Player> {
    SDL_Scancode leftKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode rightKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode fireKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode thrustKey = SDL_SCANCODE_UNKNOWN;

    inline static constexpr float bulletTimeout = 1.f;
    float lastBulletTime = bulletTimeout;
};

} // namespace game::component




