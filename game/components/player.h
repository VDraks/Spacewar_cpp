#pragma once

#include <SDL.h>

#include "ecs/component.h"

namespace game::component {

struct Player : public ecs::Component<Player> {
    SDL_Scancode leftKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode rightKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode fireKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode thrustKey = SDL_SCANCODE_UNKNOWN;

    inline static constexpr float bulletTimeout = 0.5f;
    float lastBulletTime = bulletTimeout;

    int layer = -1;

    inline static constexpr float fuelParticleTimeout = 0.01f;
    float lastFuelParticleTime = fuelParticleTimeout;
};

} // namespace game::component




