#pragma once

#include <SDL.h>

#include "ecs/component.h"

namespace game::component {

struct Player : public ecs::Component<Player> {
    SDL_Scancode leftKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode rightKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode fireKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode thrustKey = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode teleportationKey = SDL_SCANCODE_UNKNOWN;

    inline static constexpr float bulletTimeout = 0.5f;
    float bulletCooldownTime = bulletTimeout;

    inline static constexpr int bulletMaxCount = 20;
    int bulletCount = bulletMaxCount;

    int layer = -1;

    inline static constexpr float fuelParticleTimeout = 0.01f;
    float fuelParticleCooldownTime = fuelParticleTimeout;

    inline static constexpr float fuelMaxValue = 20.f;
    float fuelValue = fuelMaxValue;

    inline static constexpr float teleportationTimeout = 3.0f;
    float teleportationCooldownTime = teleportationTimeout;
};

} // namespace game::component