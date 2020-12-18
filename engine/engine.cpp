#include "engine.h"

#include <iostream>
#include <SDL2/SDL.h>

Engine::Engine():
    _view(_world) {

}

void Engine::run() {
    std::cout << "engine run" << std::endl;

    int close = 0;

    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_KEYDOWN:
                    std::cout << "event.key.keysym.scancode: " << event.key.keysym.scancode << std::endl;
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            _world.gameObject.y -= 10;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            _world.gameObject.x -= 10;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            _world.gameObject.y += 10;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            _world.gameObject.x += 10;
                            break;
                    }
            }
        }

        // right boundary
        if (_world.gameObject.x > 1000)
            _world.gameObject.x = 1000;

        // left boundary
        if (_world.gameObject.x < 0)
            _world.gameObject.x = 0;

        // bottom boundary
        if (_world.gameObject.y > 1000)
            _world.gameObject.y = 1000;

        // upper boundary
        if (_world.gameObject.y < 0)
            _world.gameObject.y = 0;

        _view.render();

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
}