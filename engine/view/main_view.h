#pragma once

#include <SDL2/SDL.h>

class MainView {
public:
    MainView();
    ~MainView();

    void render();

private:
    SDL_Window* win;
    SDL_Renderer* rend;
};


