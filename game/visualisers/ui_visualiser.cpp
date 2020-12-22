#include "ui_visualiser.h"

namespace game::visualiser {

UiVisualiser::UiVisualiser(const GameController& gameController):
        _gameController(gameController) {
}

void UiVisualiser::render(view::IVisualiserContext* context) {

    const auto size = _gameController.world().worldSize();

    context->drawText(std::to_string(_gameController.playerScores().at(0)), math::Vec2 { 30.f, 30.f });
    context->drawText(std::to_string(_gameController.playerScores().at(1)), math::Vec2 { size.x - 30.f, 30.f });
}

} // namespace game::visualiser