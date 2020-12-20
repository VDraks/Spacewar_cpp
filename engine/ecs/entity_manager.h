#pragma once

#include "entity_set.h"
#include "component.h"

namespace ecs {

template<typename T>
class Component;

class EntityManager {
public:
    static constexpr auto UndefinedEntity = static_cast<Entity>(std::numeric_limits<std::underlying_type_t<Entity>>::max());

    EntityManager() {
        const auto componentCount = BaseComponent::getComponentCount();
        // Component containers
        _componentContainers.resize(componentCount);
        for (auto type = std::size_t(0); type < _componentContainers.size(); ++type) {
            _componentContainers[type] = BaseComponent::createComponentContainer(type);
        }

        // Entity sets
        _componentToEntitySets.resize(componentCount);
        _entitySets.resize(BaseEntitySet::getEntitySetCount());
        for (auto type = std::size_t(0); type < _entitySets.size(); ++type) {
            _entitySets[type] = BaseEntitySet::createEntitySet(type, _entities, _componentContainers,
                                                               _componentToEntitySets);
        }
    }

    EntityManager(const EntityManager&) = delete;

    void reserve(std::size_t size) {
        _entities.reserve(size);
    }

    // Entities

    [[nodiscard]] bool hasEntity(Entity entity) const {
        return _entities.has(entity);
    }

    Entity createEntity() {
        return _entities.emplace().first;
    }

    void removeEntity(Entity entity) {
        const auto& entityData = _entities.get(entity);
        // Remove components
        for (auto& [componentType, componentId] : entityData.getComponents())
            _componentContainers[componentType]->remove(componentId);
        // Send message to entity sets
        for (auto entitySetType : entityData.getEntitySets())
            _entitySets[entitySetType]->onEntityRemoved(entity);
        // Remove entity
        _entities.erase(entity);
    }

    // Components

    template<typename T>
    [[nodiscard]] bool hasComponent(Entity entity) const {
        checkComponentType<T>();
        return _entities.get(entity).hasComponent<T>();
    }

    template<typename ...Ts>
    [[nodiscard]] bool hasComponents(Entity entity) const {
        checkComponentTypes<Ts...>();
        return _entities.get(entity).hasComponents<Ts...>();
    }

    template<typename T>
    [[nodiscard]] T& getComponent(Entity entity) {
        checkComponentType<T>();
        return getComponentSparseSet<T>().get(_entities.get(entity).getComponent<T>());
    }

    template<typename T>
    [[nodiscard]] const T& getComponent(Entity entity) const {
        checkComponentType<T>();
        return getComponentSparseSet<T>().get(_entities.get(entity).getComponent<T>());
    }

    template<typename ...Ts>
    [[nodiscard]] std::tuple<Ts&...> getComponents(Entity entity) {
        checkComponentTypes<Ts...>();
        auto& entityData = _entities.get(entity);
        return std::tie(getComponentSparseSet<Ts>().get(entityData.getComponent<Ts>())...);
    }

    template<typename ...Ts>
    [[nodiscard]] std::tuple<const Ts&...> getComponents(Entity entity) const {
        checkComponentTypes<Ts...>();
        auto& entityData = _entities.get(entity);
        return std::tie(std::as_const(getComponentSparseSet<Ts>().get(entityData.getComponent<Ts>()))...);
    }

    template<typename T, typename ...Args>
    T& addComponent(Entity entity, Args&&... args) {
        checkComponentType<T>();
        auto [componentId, component] = getComponentSparseSet<T>().emplace(std::forward<Args>(args)...);
        _entities.get(entity).addComponent<T>(componentId);
        // Send message to entity sets
        for (auto entitySet : _componentToEntitySets[T::Type])
            entitySet->onEntityUpdated(entity);
        // Return the created component
        return component;
    }

    template<typename T>
    void removeComponent(Entity entity) {
        checkComponentType<T>();
        // Remove component from entity and component container
        getComponentSparseSet<T>().erase(_entities.get(entity).removeComponent<T>());
        // Send message to entity sets
        for (auto entitySet : _componentToEntitySets[T::Type])
            entitySet->onEntityUpdated(entity);
    }

    // Entity sets

    template<typename ...Ts>
    [[nodiscard]] EntitySet<Ts...>& getEntitySet() {
        checkComponentTypes<Ts...>();
        return *static_cast<EntitySet<Ts...>*>(_entitySets[EntitySet<Ts...>::Type].get());
    }

    template<typename ...Ts>
    [[nodiscard]] const EntitySet<Ts...>& getEntitySet() const {
        checkComponentTypes<Ts...>();
        return *static_cast<EntitySet<Ts...>*>(_entitySets[EntitySet<Ts...>::Type].get());
    }

private:
    std::vector<std::unique_ptr<BaseComponentContainer>> _componentContainers;
    EntityContainer _entities;
    std::vector<std::unique_ptr<BaseEntitySet>> _entitySets;
    std::vector<std::vector<BaseEntitySet*>> _componentToEntitySets;


    template<typename T>
    ComponentSparseSet<T>& getComponentSparseSet() {
        return static_cast<ComponentContainer<T>*>(_componentContainers[T::Type].get())->components;
    }

    template<typename T>
    const ComponentSparseSet<T>& getComponentSparseSet() const {
        return static_cast<const ComponentContainer<T>*>(_componentContainers[T::Type].get())->components;
    }
};

} // namespace ecs