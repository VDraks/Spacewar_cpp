#pragma once

#include <SDL.h>
#include <unordered_set>

namespace controller {

class InputController {
public:
    void readInput();

    [[nodiscard]] bool isPressed(SDL_Scancode key) const;
    [[nodiscard]] bool isClose() const;
    // TODO clicked
private:
    std::unordered_set<SDL_Scancode> _keysDown;
    bool _close = false;
};

} // namespace controller


