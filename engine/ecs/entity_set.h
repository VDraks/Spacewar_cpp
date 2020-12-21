#pragma once

#include <functional>
#include <memory>
#include "component_container.h"
#include "entity_set_iterator.h"
#include "entity_set_type.h"
#include "entity_container.h"

namespace ecs {

template<typename ...Ts>
class EntitySet;

class BaseEntitySet {
public:
    static std::size_t getEntitySetCount() {
        return sFactories().size();
    }

    static std::unique_ptr<BaseEntitySet> createEntitySet(std::size_t type,
                                                          EntityContainer& entities,
                                                          const std::vector<std::unique_ptr<BaseComponentContainer>>& componentContainers,
                                                          std::vector<std::vector<BaseEntitySet *>>& componentToEntitySets) {
        return sFactories()[type](entities, componentContainers, componentToEntitySets);
    }

    BaseEntitySet() = default;
    virtual ~BaseEntitySet() = default;

    bool hasEntity(Entity entity) const {
        return _entityToIndex.find(entity) != std::end(_entityToIndex);
    }

    void onEntityUpdated(Entity entity) {
        const auto satisfied = satisfyRequirements(entity);
        const auto managed = hasEntity(entity);
        if (satisfied && !managed)
            addEntity(entity);
        else if (!satisfied && managed)
            removeEntity(entity, true);
    }

    void onEntityRemoved(Entity entity) {
        removeEntity(entity, false);
    }

protected:
    virtual bool satisfyRequirements(Entity entity) = 0;

    virtual void addEntity(Entity entity) = 0;

    virtual void removeEntity(Entity entity, bool updateEntity) = 0;

    std::unordered_map<Entity, std::size_t> _entityToIndex;

    template<typename ...Ts>
    static EntitySetType generateEntitySetType() {
        sFactories().push_back([](EntityContainer& entities,
                                const std::vector<std::unique_ptr<BaseComponentContainer>>& componentContainers,
                                std::vector<std::vector<BaseEntitySet *>>& componentToEntitySets)
                                     -> std::unique_ptr<BaseEntitySet> {
            auto entitySet = std::make_unique<EntitySet<Ts...>>(entities,
                                                                std::tie(
                                                                        static_cast<ComponentContainer<Ts> *>(componentContainers[Ts::Type].get())->components...));
            (componentToEntitySets[Ts::Type].push_back(entitySet.get()), ...);
            return std::move(entitySet);
        });
        return sFactories().size() - 1;
    }

private:
    using EntitySetFactory = std::unique_ptr<BaseEntitySet>(*)(
            EntityContainer&,
            const std::vector<std::unique_ptr<BaseComponentContainer>>&,
            std::vector<std::vector<BaseEntitySet *>>&);

    static std::vector<EntitySetFactory>& sFactories() {
        static std::vector<EntitySetFactory> instance;
        return instance;
    };
};

template<typename ...Ts>
class EntitySet : public BaseEntitySet {
    using ValueType = std::pair<Entity, std::array<ComponentId, sizeof...(Ts)>>;
    using UIterator = typename std::vector<ValueType>::iterator; // Underlying iterator
    using UConstIterator = typename std::vector<ValueType>::const_iterator; // Underlying const iterator
    using ComponentContainers = std::tuple<ComponentSparseSet<Ts>& ...>;

public:
    using Iterator = EntitySetIterator<UIterator, Ts...>;
    using ConstIterator = EntitySetIterator<UConstIterator, const Ts...>;
    using ListenerId = uint32_t;
    using EntityAddedListener = std::function<void(Entity)>;
    using EntityRemovedListener = std::function<void(Entity)>;

    static const EntitySetType Type;

    EntitySet(EntityContainer& entities, const ComponentContainers& componentContainers) :
            _entities(entities), _componentContainers(componentContainers) {

    }

    std::size_t getSize() const {
        return _managedEntities.size();
    }

    Iterator begin() {
        return Iterator(_managedEntities.begin(), _componentContainers);
    }

    ConstIterator begin() const {
        return ConstIterator(_managedEntities.begin(), _componentContainers);
    }

    Iterator end() {
        return Iterator(_managedEntities.end(), _componentContainers);
    }

    ConstIterator end() const {
        return ConstIterator(_managedEntities.end(), _componentContainers);
    }

    // Listeners

    ListenerId addEntityAddedListener(EntityAddedListener listener) {
        return _entityAddedListeners.emplace(std::move(listener)).first;
    }

    void removeEntityAddedListener(ListenerId listenerId) {
        _entityAddedListeners.erase(listenerId);
    }

    ListenerId addEntityRemovedListener(EntityRemovedListener listener) {
        return _entityRemovedListeners.emplace(std::move(listener)).first;
    }

    void removeEntityRemovedListener(ListenerId listenerId) {
        _entityRemovedListeners.erase(listenerId);
    }

protected:
    bool satisfyRequirements(Entity entity) override {
        return _entities.get(entity).template hasComponents<Ts...>();
    }

    void addEntity(Entity entity) override {
        _entityToIndex[entity] = _managedEntities.size();
        auto& entityData = _entities.get(entity);
        entityData.addEntitySet(Type);
        _managedEntities.emplace_back(entity, std::array<ComponentId, sizeof...(Ts)>{
                entityData.template getComponent<Ts>()...});
        // Call listeners
        for (const auto& listener : _entityAddedListeners.getObjects())
            listener(entity);
    }

    void removeEntity(Entity entity, bool updateEntity) override {
        // Call listeners
        for (const auto& listener : _entityRemovedListeners.getObjects())
            listener(entity);
        auto it = _entityToIndex.find(entity);
        auto index = it->second;
        _entityToIndex[_managedEntities.back().first] = index;
        _entityToIndex.erase(it);
        _managedEntities[index] = _managedEntities.back();
        _managedEntities.pop_back();
        if (updateEntity)
            _entities.get(entity).removeEntitySet(Type);
    }

private:
    std::vector<ValueType> _managedEntities;
    EntityContainer& _entities;
    ComponentContainers _componentContainers;
    SparseSet<ListenerId, EntityAddedListener> _entityAddedListeners;
    SparseSet<ListenerId, EntityRemovedListener> _entityRemovedListeners;
};

template<typename ...Ts>
const EntitySetType EntitySet<Ts...>::Type = BaseEntitySet::generateEntitySetType<Ts...>();

} // namespace ecs