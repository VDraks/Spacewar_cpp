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

    SDL_Rect Message_rect;
    Message_rect.w = text.size() * 15;
    Message_rect.h = 30;
    Message_rect.x = static_cast<int>(pos.x) - Message_rect.w / 2;
    Message_rect.y = static_cast<int>(pos.y) - Message_rect.h / 2;

    SDL_RenderCopy(_rend, message, nullptr, &Message_rect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

} // namespace view