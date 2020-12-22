#include "particle_system_visualiser.h"

#include "model/components/particle_system.h"
#include "model/components/transform.h"

namespace view::visualiser {

using namespace model::component;

ParticleSystemVisualiser::ParticleSystemVisualiser(const model::World& world) : _world(world) {}

void ParticleSystemVisualiser::render(IVisualiserContext* context) {
    for (const auto& [entity, components] : _world.entityManager().getEntitySet<Transform, ParticleSystem>()) {
        const auto& [transform, particle] = components;

        DrawSettings settings;
        settings.color = particle.settings.color;

        for (auto point : particle.points) {
            point = point * particle.scale;
            point = point + particle.shapeSettings.offset;
            point = transform.applyToPoint(point);
            context->drawPoint(point, settings);
        }
    }
}

} // namespace view::visualiser