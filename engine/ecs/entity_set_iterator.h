#pragma once

#include <array>
#include <tuple>
#include <utility>
#include "component_sparse_set.h"
#include "entity.h"

namespace ecs {

template<typename Iterator, typename ...Ts>
class EntitySetIterator {
    using ComponentContainers = std::tuple<ComponentSparseSet<std::remove_const_t<Ts>>& ...>;

public:
    explicit EntitySetIterator(Iterator it, const ComponentContainers& componentContainers) :
            _it(it), _componentContainers(componentContainers) {

    }

    bool operator!=(const EntitySetIterator<Iterator, Ts...>& it) {
        return _it != it._it;
    }

    std::pair<Entity, std::tuple<Ts& ...>> operator*() {
        return std::pair(_it->first, getComponentsByIds(_it->second, std::index_sequence_for<Ts...>{}));
    }

    EntitySetIterator<Iterator, Ts...>& operator++() {
        ++_it;
        return *this;
    }

private:
    Iterator _it;
    const ComponentContainers& _componentContainers;

    template<std::size_t ...Is>
    std::tuple<Ts& ...>
    getComponentsByIds(const std::array<ComponentId, sizeof...(Ts)>& componentIds, std::index_sequence<Is...>) {
        return std::tie(std::get<Is>(_componentContainers).get(componentIds[Is])...);
    }

    template<std::size_t ...Is>
    std::tuple<const Ts&...>
    getComponentsByIds(const std::array<ComponentId, sizeof...(Ts)>& componentIds, std::index_sequence<Is...>) const {
        return std::tie(std::as_const(std::get<Is>(_componentContainers).get(componentIds[Is]))...);
    }
};

} // namespace ecs