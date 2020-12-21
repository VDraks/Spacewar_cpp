#pragma once

#include <memory>

namespace model {
class World;
} // namespace model

class MainView {
public:
    explicit MainView(const model::World& world);
    ~MainView();

    void render();

private:
    struct Impl;
    std::unique_ptr<Impl> _d;
};


