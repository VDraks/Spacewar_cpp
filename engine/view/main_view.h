#pragma once

#include <memory>

#include "view/i_visualiser.h"

namespace model {
class World;
} // namespace model

namespace view {

class MainView {
public:
    explicit MainView(const model::World& world);
    ~MainView();

    void render();

    void addVisualiser(std::unique_ptr<IVisualiser>&& visualiser);

private:
    struct Impl;
    std::unique_ptr<Impl> _d;
};

} // namespace view