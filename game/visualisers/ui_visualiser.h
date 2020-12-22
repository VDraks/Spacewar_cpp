#pragma once

#include "game/game_controller.h"
#include "view/i_visualiser.h"

namespace game::visualiser {

class UiVisualiser : public view::IVisualiser {
public:
    explicit UiVisualiser(const GameController& gameController);

    void render(view::IVisualiserContext* context) override;

private:
    const GameController& _gameController;
};

} // namespace game::visualiser