#pragma once

#include "engine.h"

namespace game {

class Game {
public:
    Game();

    void run();

private:
    Engine _engine;
};

} // namespace game


