#pragma once

#include <unordered_map>
#include <unordered_set>
#include "component_id.h"
#include "component_type.h"
#include "entity.h"
#include "entity_set_type.h"
#include "sparse_set.h"

namespace ecs {

class EntityData {
    using ComponentIdContainer = std::unordered_map<ComponentType, ComponentId>;
    using EntitySetTypeContainer = std::unordered_set<EntitySetType>;

public:
    // Components

    template<typename T>
    bool hasComponent() const {
        return findComponent<T>() != std::end(_componentIds);
    }

    template<typename ...Ts>
    bool hasComponents() const {
        return (hasComponent<Ts>() && ...);
    }

    template<typename T>
    ComponentId getComponent() const {
        return findComponent<T>()->second;
    }

    const ComponentIdContainer& getComponents() const {
        return _componentIds;
    }

    template<typename T>
    void addComponent(ComponentId componentId) {
        _componentIds[T::Type] = componentId;
    }

    template<typename T>
    ComponentId removeComponent() {
        auto it = findComponent<T>();
        auto componentId = it->second;
        _componentIds.erase(it);
        return componentId;
    }

    // Types

    const EntitySetTypeContainer& getEntitySets() const {
        return _entitySetTypes;
    }

    void addEntitySet(EntitySetType entitySetType) {
        _entitySetTypes.insert(entitySetType);
    }

    void removeEntitySet(EntitySetType entitySetType) {
        _entitySetTypes.erase(entitySetType);
    }

private:
    ComponentIdContainer _componentIds;
    EntitySetTypeContainer _entitySetTypes;

    template<typename T>
    ComponentIdContainer::const_iterator findComponent() const {
        return _componentIds.find(T::Type);
    }
};

using EntityContainer = SparseSet<Entity, EntityData>;

} // namespace ecs