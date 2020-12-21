#include "engine.h"

#include <iostream>
#include <SDL.h>

Engine::Engine():
    _view(_world) {

}

void Engine::run() {
    std::cout << "engine run" << std::endl;

    float lastTime = SDL_GetTicks();

    while (!_inputController.isClose()) {
        float nowTime = SDL_GetTicks();
        float deltaTime = (nowTime - lastTime) / 1000.f;
        lastTime = nowTime;

        _inputController.readInput();

        for (const auto& system : _systems) {
            system->update(deltaTime, _world.entityManager());
        }

        _view.render();

//        // calculates to 60 fps
//        SDL_Delay(1000 / 60);
    }
}

void Engine::addSystem(std::unique_ptr<ecs::System>&& system) {
    _systems.push_back(std::move(system));
}
