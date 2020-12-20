#include "engine.h"

#include <iostream>
#include <SDL2/SDL.h>

Engine::Engine():
    _view(_world) {

}

void Engine::run() {
    std::cout << "engine run" << std::endl;

    while (!_inputController.isClose()) {

        float dt = 1000.f / 60;

        _inputController.readInput();

        for (const auto& system : _systems) {
            system->update(dt, _world.entityManager());
        }

        _view.render();

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
}

void Engine::addSystem(std::unique_ptr<ecs::System>&& system) {
    _systems.push_back(std::move(system));
}
