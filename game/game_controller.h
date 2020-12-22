#pragma once

#include "engine.h"

namespace game {

class GameController {
public:
    enum class Player {
        First = 0,
        Second = 1
    };

    explicit GameController(Engine& engine);

    void startGame();
    void startMatch();

    void addScore(Player player);

    [[nodiscard]] const std::array<int, 2>& playerScores() const { return _playerScores; }

    [[nodiscard]] const model::World& world() const { return _engine.world(); }

private:
    Engine& _engine;
    std::array<int, 2> _playerScores = { 0, 0 };
};

} // namespace game


