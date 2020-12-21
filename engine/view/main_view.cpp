#include "main_view.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>

#include "model/components/transform.h"
#include "model/components/shape.h"
#include "model/world.h"

void DrawShape(const model::component::Shape& shape, const SDL_Color& color, SDL_Renderer* renderer, const model::component::Transform& transform) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const auto applyTransform = [](const math::Point& point, const model::component::Transform& transform) {
        const float x =
                point.x * std::cos(transform.angle) - point.y * std::sin(transform.angle) + transform.position.x;
        const float y =
                point.y * std::cos(transform.angle) + point.x * std::sin(transform.angle) + transform.position.y;
        return math::Point{x, y};
    };

    const auto drawLine = [renderer, &transform, applyTransform](const math::Point& start, const math::Point& end) {
        const auto newStart = applyTransform(start, transform);
        const auto newEnd = applyTransform(end, transform);
        SDL_RenderDrawLine(renderer, newStart.x, newStart.y, newEnd.x, newEnd.y);
    };

    for (int i = 0; i < shape.points.size() - 1; ++i) {
        drawLine(shape.points[i], shape.points[i + 1]);
    }
    drawLine(shape.points.back(), shape.points[0]);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void DrawText(TTF_Font* font, const std::string& text, SDL_Renderer* renderer) {
    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 100;  //controls the rect's x coordinate
    Message_rect.y = 100; // controls the rect's y coordinte
    Message_rect.w = 300; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, message, NULL, &Message_rect); //you put the renderer's name first, the message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

//Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

struct MainView::Impl {

    const model::World& world;
    SDL_Window* win = nullptr;
    SDL_Renderer* rend = nullptr;
    TTF_Font* font = nullptr;

    explicit Impl(const model::World& world):
        world(world) {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "error initializing SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }

        if(TTF_Init() == -1) {
            std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
            exit(2);
        }

        font = TTF_OpenFont("OpenSans-Regular.ttf", 16);
        if (font == nullptr){
            std::cout << "TTF_OpenFont" << std::endl;
            exit(3);
        }

        win = SDL_CreateWindow("Spacewar",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                               world.worldSize().x, world.worldSize().y, 0);

        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        rend = SDL_CreateRenderer(win, -1, render_flags);
    }

    ~Impl() {
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
    }
};

MainView::MainView(const model::World& world):
    _d(std::make_unique<Impl>(world)) {
}

MainView::~MainView() = default;

void MainView::render() {
    SDL_SetRenderDrawColor(_d->rend, 0, 0, 255, 255);

    SDL_RenderClear(_d->rend);

    const auto& shapes = _d->world.entityManager().getEntitySet<model::component::Transform, model::component::Shape>();
    for (const auto& [entity, components] : shapes) {
        const auto& [transform, shape] = components;
        DrawShape(shape, SDL_Color{0, 255, 0, 255}, _d->rend, transform);
    }

    DrawText(_d->font, "TEST TEXT!", _d->rend);

    SDL_RenderPresent(_d->rend);
}