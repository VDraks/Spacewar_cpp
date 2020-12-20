#include "input_controller.h"

namespace controller {

void InputController::readInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _close = true;
                break;
            case SDL_KEYDOWN:
                _keysDown.insert(event.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                _keysDown.erase(event.key.keysym.scancode);
                break;
        }
    }
}

bool InputController::isPressed(SDL_Scancode key) const {
    return _keysDown.count(key) > 0;
}

bool InputController::isClose() const {
    return _close;
}

} // namespace controller