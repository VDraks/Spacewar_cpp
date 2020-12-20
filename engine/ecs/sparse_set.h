#pragma once

#include <vector>

namespace ecs {

template<typename Id, typename T>
class SparseSet {
    static constexpr auto Undefined = std::numeric_limits<std::size_t>::max();

public:
    template<typename ...Args>
    std::pair<Id, T&> emplace(Args&&... args) {
        // Add object
        const std::size_t i = _objects.size();
        auto& object = _objects.emplace_back(std::forward<Args>(args)...);

        // Get the correct id and set the links
        Id id;
        if (_freeIds.empty()) {
            id = static_cast<Id>(_idToIndex.size());
            _idToIndex.push_back(i);
        } else {
            id = _freeIds.back();
            _freeIds.pop_back();
            _idToIndex[static_cast<std::size_t>(id)] = i;
        }
        _indexToId.push_back(id);
        return std::pair<Id, T&>(id, object);
    }

    [[nodiscard]] bool has(Id id) const {
        return static_cast<std::size_t>(id) < _idToIndex.size() &&
               _idToIndex[static_cast<std::size_t>(id)] != Undefined;
    }

    [[nodiscard]] T& get(Id id) {
        return _objects[_idToIndex[static_cast<std::size_t>(id)]];
    }

    [[nodiscard]] const T& get(Id id) const {
        return _objects[_idToIndex[static_cast<std::size_t>(id)]];
    }

    void erase(Id id) {
        // Get the index of the object to destroy
        const std::size_t i = _idToIndex[static_cast<std::size_t>(id)];
        // Swap with the last object and update its index
        // Moving std::unordered_map may causes a segfault
        std::swap(_objects[i], _objects.back());
        //_objects[i] = std::move(_objects.back());
        const Id lastObjectId = _indexToId.back();
        _idToIndex[static_cast<std::size_t>(lastObjectId)] = i;
        _indexToId[i] = lastObjectId;
        // Erase the last object and its index
        _objects.pop_back();
        _indexToId.pop_back();
        // Assign Undefined to the id
        _idToIndex[static_cast<std::size_t>(id)] = Undefined;
        // Add the deleted Id to the free Ids
        _freeIds.push_back(id);
    }

    [[nodiscard]] std::vector<T>& getObjects() {
        return _objects;
    }

    [[nodiscard]] const std::vector<T>& getObjects() const {
        return _objects;
    }

    [[nodiscard]] std::size_t getSize() const {
        return _objects.size();
    }

    void reserve(std::size_t size) {
        _idToIndex.reserve(size);
        _indexToId.reserve(size);
        _freeIds.reserve(size);
        _objects.reserve(size);
    }

private:
    std::vector<std::size_t> _idToIndex;
    std::vector<Id> _indexToId;
    std::vector<Id> _freeIds;
    std::vector<T> _objects;
};

} // namespace ecs