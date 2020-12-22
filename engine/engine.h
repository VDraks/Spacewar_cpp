#pragma once

#include "controller/input_controller.h"
#include "ecs/system.h"
#include "model/world.h"
#include "view/main_view.h"

class Engine {
public:
    Engine();

    void run();

    [[nodiscard]] model::World& world() { return _world; }

    [[nodiscard]] const controller::InputController& inputController() const { return _inputController; }

    template<typename T, typename ...Args>
    void addSystem(Args&&... args) {
        addSystem(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void addSystem(std::unique_ptr<ecs::System>&& system);

    template<typename T, typename ...Args>
    void addVisualiser(Args&&... args) {
        addVisualiser(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void addVisualiser(std::unique_ptr<view::IVisualiser>&& visualiser);

private:
    model::World _world;
    view::MainView _view;
    controller::InputController _inputController;

    std::vector<std::unique_ptr<ecs::System>> _systems;
};
