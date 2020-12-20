#pragma once

#include <SDL2/SDL.h>

namespace model {
class World;
} // namespace model

class MainView {
public:
    explicit MainView(const model::World& world);
    ~MainView();

    void render();

private:
    const model::World& _world;

    SDL_Window* _win = nullptr;
    SDL_Renderer* _rend = nullptr;
};


