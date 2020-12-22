#pragma once

#include "SDL.h"

namespace game {

struct GameConfig {
    // Ship
    constexpr static SDL_Color shipColor = { 227, 255, 250, 255 };
    constexpr static SDL_Color bulletColor = { 61, 255, 171, 255 };
    constexpr static SDL_Color fuelColor = { 230, 172, 39, 255 };

    // Star
    constexpr static SDL_Color starColor = { 255, 247, 15, 255 };
};

} // namespace game


