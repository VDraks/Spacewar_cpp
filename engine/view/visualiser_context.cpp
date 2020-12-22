#include "visualiser_context.h"

namespace view {

VisualiserContext::VisualiserContext(SDL_Renderer* rend, TTF_Font* font) :
        _rend(rend),
        _font(font) {
}

void VisualiserContext::drawText(const std::string& text, const math::Vec2& pos) {
    const SDL_Color color = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, text.c_str(), color);

    SDL_Texture* message = SDL_CreateTextureFromSurface(_rend, surfaceMessage);

    SDL_FRect textRect;
    textRect.w = text.size() * 15.f;
    textRect.h = 30.f;
    textRect.x = pos.x - textRect.w / 2;
    textRect.y = pos.y - textRect.h / 2;

    SDL_RenderCopyF(_rend, message, nullptr, &textRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void VisualiserContext::drawPoint(const math::Vec2& point, const DrawSettings& settings) {
    const auto& color = settings.color;
    SDL_SetRenderDrawColor(_rend,  color.r, color.g, color.b, color.a);
    SDL_RenderDrawPointF(_rend, point.x, point.y);
}

void VisualiserContext::drawRect(const math::Vec2& point, const math::Vec2& size, const DrawSettings& settings) {
    const auto& color = settings.color;
    SDL_SetRenderDrawColor(_rend,  color.r, color.g, color.b, color.a);
    SDL_FRect rect;
    rect.w = size.x;
    rect.h = size.y;
    rect.x = point.x;
    rect.y = point.y;
    if (settings.fill) {
        SDL_RenderFillRectF(_rend, &rect);
    } else {
        SDL_RenderDrawRectF(_rend, &rect);
    }
}

} // namespace view