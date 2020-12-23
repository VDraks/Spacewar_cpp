#include "engine.h"

#include <iostream>

#include "model/systems/particle_system.h"
#include "view/visualisers/particle_system_visualiser.h"

Engine::Engine():
    _view(_world) {

    addSystem<model::system::ParticleSystem>();

    addVisualiser<view::visualiser::ParticleSystemVisualiser>(_world);
}

void Engine::run() {
    auto lastTime = static_cast<float>(SDL_GetTicks());

    while (!_inputController.isClose()) {
        auto nowTime = static_cast<float>(SDL_GetTicks());
        float deltaTime = (nowTime - lastTime) / 1000.f;
        lastTime = nowTime;

        _inputController.readInput();

        for (const auto& system : _systems) {
            system->update(deltaTime, _world.entityManager());
        }

        _view.render();
    }
}

void Engine::addSystem(std::unique_ptr<ecs::System>&& system) {
    _systems.push_back(std::move(system));
}

void Engine::addVisualiser(std::unique_ptr<view::IVisualiser>&& visualiser) {
    _view.addVisualiser(std::move(visualiser));
}