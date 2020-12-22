#include "main_view.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>

#include "model/components/transform.h"
#include "model/components/shape.h"
#include "model/world.h"
#include "view/visualiser_context.h"

namespace view {

using namespace model::component;

void DrawShape(const Shape& shape, const SDL_Color& color, SDL_Renderer* renderer, const Transform& transform) {
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

struct MainView::Impl {

    const model::World& world;
    SDL_Window* win = nullptr;
    SDL_Renderer* rend = nullptr;
    TTF_Font* font = nullptr;

    std::unique_ptr<VisualiserContext> context;

    std::vector<std::unique_ptr<IVisualiser>> visualisers;

    explicit Impl(const model::World& world) :
            world(world) {

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "error initializing SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }

        if (TTF_Init() == -1) {
            std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
            exit(2);
        }

        font = TTF_OpenFont("OpenSans-Regular.ttf", 30);
        if (font == nullptr) {
            std::cout << "TTF_OpenFont" << std::endl;
            exit(3);
        }

        win = SDL_CreateWindow("Spacewar",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               world.worldSize().x, world.worldSize().y, 0);

        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        rend = SDL_CreateRenderer(win, -1, render_flags);

        context = std::make_unique<VisualiserContext>(rend, font);

        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
    }

    ~Impl() {
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
    }
};

MainView::MainView(const model::World& world) :
        _d(std::make_unique<Impl>(world)) {
}

MainView::~MainView() = default;

void MainView::render() {
    SDL_SetRenderDrawColor(_d->rend, 0, 0, 0, 255);

    SDL_RenderClear(_d->rend);

    const auto& shapes = _d->world.entityManager().getEntitySet<model::component::Transform, model::component::Shape>();
    for (const auto& [entity, components] : shapes) {
        const auto& [transform, shape] = components;
        DrawShape(shape, SDL_Color{0, 255, 0, 255}, _d->rend, transform);
    }

    for (const auto& visualiser : _d->visualisers) {
        visualiser->render(_d->context.get());
    }

    SDL_RenderPresent(_d->rend);
}

void MainView::addVisualiser(std::unique_ptr<IVisualiser>&& visualiser) {
    _d->visualisers.push_back(std::move(visualiser));
}

} // namespace view