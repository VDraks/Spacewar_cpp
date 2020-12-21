#pragma once

#include <array>

#include "ecs/component.h"

namespace game::component::event {

struct EntitiesCollided : public ecs::Component<EntitiesCollided> {
    using Pair = std::array<ecs::Entity, 2>;
    Pair entities = {};
};

} // namespace game::component::event

