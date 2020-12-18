#include "main_view.h"

#include "world.h"

#include <vector>

#include <SDL2/SDL.h>
#include <iostream>
//#include <SDL2/SDL_image.h>

class Point {
public:
    Point() = default;
    Point(int x, int y) { this->x = x; this->y = y; };
    int x, y;
};

void DrawFilledPolygon(const std::vector<Point>& vertices, const SDL_Color& color, SDL_Renderer* renderer, const Point& offset) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    std::cout << "x: " << offset.x << ", y: " << offset.y << std::endl;

    for (int i = 0; i < vertices.size() - 1; ++i) {
        SDL_RenderDrawLine(renderer,
                           vertices[i].x + offset.x, vertices[i].y + offset.y,
                           vertices[i + 1].x + offset.x, vertices[i + 1].y + offset.y);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

MainView::MainView(const World& world):
    _world(world) {

    std::cout << "MainView()" << std::endl;
    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    rend = SDL_CreateRenderer(win, -1, render_flags);
}

MainView::~MainView() {
    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);
}

void MainView::render() {
    SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);

    // clears the screen
    SDL_RenderClear(rend);

    DrawFilledPolygon({Point(0, 0), Point(50, 0), Point(50, 50), Point(0, 50)},
                      SDL_Color{0, 255, 0, 255}, rend, Point(_world.gameObject.x, _world.gameObject.y));

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(rend);
}