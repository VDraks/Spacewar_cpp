#include "particle_system.h"

#include "math/utils.h"
#include "model/components/particle_system.h"

namespace model::system {

namespace {
float calcTimeFactor(float time, float duration) {
    const int count = static_cast<int>(time / duration);
    const float loopTime = time - duration * static_cast<float>(count);
    const float finalTime = count % 2 == 0 ? loopTime : (duration - loopTime);
    return finalTime / duration;
}
} // namespace

void ParticleSystem::update(float dt, ecs::EntityManager& entityManager) {
    std::vector<ecs::Entity> toRemove;

    for (auto [entity, components] : entityManager.getEntitySet<component::ParticleSystem>()) {
        auto& [particle] = components;

        if (!particle.isInit) {
            for (int i = 0; i < particle.settings.amount; ++i) {
                particle.points.push_back(generatePoint(particle.shapeSettings.radius));
            }
            particle.isInit = true;
        }

        if (!particle.settings.loop && particle.time > particle.settings.duration) {
            toRemove.push_back(entity);
        } else {
            const float timeFactor = calcTimeFactor(particle.time, particle.settings.duration) ;
            const float scale = math::Utils::lerp(particle.shapeSettings.scaleStart, particle.shapeSettings.scaleEnd, timeFactor);
            particle.scale = scale;
        }

        particle.time += dt;
    }

    for (const auto& entity : toRemove) {
        entityManager.removeEntity(entity);
    }
}

float ParticleSystem::randomRange(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(_randomDevice);
}

math::Vec2 ParticleSystem::generatePoint(float radius) {
    const float angle = randomRange(0.f, M_PI * 2.f);
    return math::Utils::angleVector(angle) * randomRange(0.f, radius);
}

} // namespace model::system