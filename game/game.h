#pragma once

#include "engine.h"
#include "game_controller.h"

namespace game {

class Game {
public:
    Game();

    void run();

private:
    Engine _engine;
    GameController _gameController;
};

} // namespace game


