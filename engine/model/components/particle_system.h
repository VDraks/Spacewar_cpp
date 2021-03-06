#pragma once

#include <SDL_pixels.h>

#include "math/vec_2.h"
#include "ecs/component.h"

namespace model::component {

struct ParticleSystem : public ecs::Component<ParticleSystem> {
    struct Settings {
        bool loop = false;
        float duration = 1.f;
        int amount = 1;
        SDL_Color color = { 255, 255, 255, 255 };
    };

    struct ShapeSettings {
        math::Vec2 offset;
        float scaleStart = 1.f;
        float scaleEnd = 1.f;
        float radius = 1.f;
    };

    Settings settings;
    ShapeSettings shapeSettings;

    bool isInit = false;
    float time = 0.f;
    float scale = 1.f;
    std::vector<math::Vec2> points;
};

} // namespace model::component