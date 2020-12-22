#pragma once

#include <string>
#include <SDL.h>

#include "math/vec_2.h"

namespace view {

struct DrawSettings {
    SDL_Color color = { 255, 255, 255, 255 };
    bool fill = false;
};

class IVisualiserContext {
public:
    virtual ~IVisualiserContext() = default;

    virtual void drawText(const std::string& text, const math::Vec2& pos) = 0;

    virtual void drawPoint(const math::Vec2& point, const DrawSettings& settings = {}) = 0;

    virtual void drawRect(const math::Vec2& point, const math::Vec2& size, const DrawSettings& settings = {}) = 0;
};

} // namespace view