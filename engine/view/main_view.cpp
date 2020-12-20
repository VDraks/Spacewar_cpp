#include "main_view.h"

#include <SDL2/SDL.h>
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

MainView::MainView(const model::World& world):
    _world(world) {

    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    _win = SDL_CreateWindow("Spacewar",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            _world.worldSize().x, _world.worldSize().y, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    _rend = SDL_CreateRenderer(_win, -1, render_flags);
}

MainView::~MainView() {
    SDL_DestroyRenderer(_rend);
    SDL_DestroyWindow(_win);
}

void MainView::render() {
    SDL_SetRenderDrawColor(_rend, 0, 0, 255, 255);

    SDL_RenderClear(_rend);

    const auto& shapes = _world.entityManager().getEntitySet<model::component::Transform, model::component::Shape>();
    for (const auto& [entity, components] : shapes) {
        const auto& [transform, shape] = components;
        DrawShape(shape, SDL_Color{0, 255, 0, 255}, _rend, transform);
    }

    SDL_RenderPresent(_rend);
}