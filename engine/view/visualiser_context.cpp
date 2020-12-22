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

    SDL_FRect Message_rect;
    Message_rect.w = text.size() * 15.f;
    Message_rect.h = 30.f;
    Message_rect.x = pos.x - Message_rect.w / 2;
    Message_rect.y = pos.y - Message_rect.h / 2;

    SDL_RenderCopyF(_rend, message, nullptr, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void VisualiserContext::drawPoint(const math::Vec2& point, const DrawSettings& settings) {
    const auto& color = settings.color;
    SDL_SetRenderDrawColor(_rend,  color.r, color.g, color.b, color.a);
    SDL_RenderDrawPointF(_rend, point.x, point.y);
}

} // namespace view