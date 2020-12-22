#pragma once

#include "model/world.h"
#include "view/i_visualiser.h"

namespace view::visualiser {

class ParticleSystemVisualiser : public view::IVisualiser {
public:
    explicit ParticleSystemVisualiser(const model::World& world);

    void render(IVisualiserContext* context) override;

private:
    const model::World& _world;
};

} // namespace view::visualiser