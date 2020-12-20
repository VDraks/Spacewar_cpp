#pragma once

#include "component_sparse_set.h"

namespace ecs {
class BaseComponent;

struct BaseComponentContainer {
    virtual ~BaseComponentContainer() = default;

    virtual BaseComponent& get(ComponentId componentId) = 0;

    virtual void remove(ComponentId componentId) = 0;
};

template<typename T>
struct ComponentContainer : public BaseComponentContainer {
    ComponentSparseSet<T> components;

    BaseComponent& get(ComponentId componentId) override {
        return components.get(componentId);
    }

    void remove(ComponentId componentId) override {
        components.erase(componentId);
    }
};

} // namespace ecs