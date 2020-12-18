#pragma once

#include <SDL2/SDL.h>

class World;

class MainView {
public:
    MainView(const World& world);
    ~MainView();

    void render();

private:
    const World& _world;

    SDL_Window* win;
    SDL_Renderer* rend;
};


