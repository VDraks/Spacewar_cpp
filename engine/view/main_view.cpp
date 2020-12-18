#include "main_view.h"

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


void DrawFilledPolygon(const std::vector<Point>& vertices, const SDL_Color color, SDL_Renderer* renderer, const SDL_Rect& offset) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < vertices.size() - 1; ++i) {
        SDL_RenderDrawLine(renderer,
                           vertices[i].x + offset.x, vertices[i].y + offset.y,
                           vertices[i + 1].x + offset.x, vertices[i + 1].y + offset.y);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

MainView::MainView() {
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

    // creates a surface to load an image into the main memory
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);

//    // please provide a path for your image
//    surface = IMG_Load("path");

    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);

    // clears main-memory
    SDL_FreeSurface(surface);

    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    // sets initial x-position of object
    dest.x = (1000 - dest.w) / 2;

    // sets initial y-position of object
    dest.y = (1000 - dest.h) / 2;

    // controls annimation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // annimation loop
    while (!close) {
        SDL_Event event;

        // Events mangement
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
                            dest.y -= speed / 30;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dest.x -= speed / 30;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dest.y += speed / 30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dest.x += speed / 30;
                            break;
                    }
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
        // clears the screen
        SDL_RenderClear(rend);


//        SDL_RenderCopy(rend, tex, NULL, &dest);

        DrawFilledPolygon({Point(0, 0), Point(50, 0), Point(50, 50), Point(0, 50)}, SDL_Color{0, 255, 0, 255}, rend, dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

// destroy texture
    SDL_DestroyTexture(tex);
}

MainView::~MainView() {
    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);
}

void MainView::render() {

}