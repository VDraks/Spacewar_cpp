#pragma once

#include "model/world.h"
#include "view/main_view.h"

class Engine {
public:
    Engine();

    void run();

private:
    World _world;
    MainView _view;
};
