#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "view/i_visualiser_context.h"

namespace view {

class VisualiserContext : public IVisualiserContext {
public:
    VisualiserContext(SDL_Renderer* rend, TTF_Font* font);

    void drawText(const std::string& text, const math::Vec2& pos) override;

private:
    SDL_Renderer* const _rend = nullptr;
    TTF_Font* const _font = nullptr;
};

} // namespace view