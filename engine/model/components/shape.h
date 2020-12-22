#pragma once

#include <SDL_pixels.h>

#include "math/vec_2.h"
#include "ecs/component.h"

namespace model::component {

struct Shape : public ecs::Component<Shape> {
    std::vector<math::Vec2> points;
    SDL_Color color = { 255, 255, 255, 255 };
};

} // namespace model::component


