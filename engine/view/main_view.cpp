#include "main_view.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "model/components/transform.h"
#include "model/components/shape.h"
#include "model/world.h"
#include "view/visualiser_context.h"

namespace view {

using namespace model::component;

void drawShape(const Shape& shape, SDL_Renderer* renderer, const Transform& transform) {
    const SDL_Color& color = shape.color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    const auto drawLine = [renderer, &transform](const math::Vec2& start, const math::Vec2& end) {
        const auto newStart = transform.applyToPoint(start);
        const auto newEnd = transform.applyToPoint(end);
        SDL_RenderDrawLineF(renderer, newStart.x, newStart.y, newEnd.x, newEnd.y);
    };

    for (std::size_t i = 0; i < shape.points.size() - 1; ++i) {
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

        initSdl();

        context = std::make_unique<VisualiserContext>(rend, font);
    }

    ~Impl() {
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        TTF_CloseFont(font);
    }

    void initSdl() {
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
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               static_cast<int>(world.worldSize().x), static_cast<int>(world.worldSize().y), 0);

        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        rend = SDL_CreateRenderer(win, -1, render_flags);



        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
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
        drawShape(shape, _d->rend, transform);
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