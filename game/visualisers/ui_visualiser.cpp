#include "ui_visualiser.h"

#include "game/game_config.h"
#include "game/collider_layer.h"
#include "game/components/player.h"

namespace game::visualiser {

namespace {
constexpr float scoreOffset = 30.f;

constexpr float rectWidth = 80.f;
constexpr float rectHeight = 10.f;
constexpr float rectOffsetX = 20.f;
constexpr float rectOffsetY = 20.f;

void drawProgressRect(view::IVisualiserContext* context, const math::Vec2& pos, const SDL_Color& color, const float valueFactor) {
    view::DrawSettings settings;
    settings.color = color;

    const math::Vec2 rectSize { rectWidth, rectHeight };
    context->drawRect(pos, rectSize, settings);

    math::Vec2 fillRect = rectSize;
    fillRect.x = rectWidth * valueFactor;
    settings.fill = true;
    context->drawRect(pos, fillRect, settings);
}

} // namespace

UiVisualiser::UiVisualiser(const GameController& gameController):
        _gameController(gameController) {
}

void UiVisualiser::render(view::IVisualiserContext* context) {

    const auto size = _gameController.world().worldSize();

    context->drawText(std::to_string(_gameController.playerScores().at(0)), math::Vec2 { scoreOffset, scoreOffset });
    context->drawText(std::to_string(_gameController.playerScores().at(1)), math::Vec2 { size.x - scoreOffset, scoreOffset });

    for (const auto& [entity, components] : _gameController.world().entityManager().getEntitySet<game::component::Player>()) {
        const auto& [player] = components;

        const float x = player.layer == static_cast<int>(game::ColliderLayer::FirstPlayer)
                ? rectOffsetX
                : (size.x - rectOffsetX - rectWidth);

        math::Vec2 pos{x, size.y - rectOffsetY};
        drawProgressRect(context, pos, GameConfig::fuelColor, player.fuelValue / game::component::Player::fuelMaxValue);

        pos.y -= rectOffsetY * 1.2f;
        drawProgressRect(context, pos, GameConfig::bulletColor, static_cast<float>(player.bulletCount) / game::component::Player::bulletMaxCount);
    }
}

} // namespace game::visualiser