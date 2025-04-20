#pragma once
#include "Entity.h"
#include <unordered_map>
#include <vector>

class Registry {
public:
  Entity createEntity() { return nextId++; }

  template <typename T> void addComponent(Entity e, T component) {
    auto &map = getMap<T>();
    map[e] = component;
  }

  template <typename T> bool hasComponent(Entity e) {
    return getMap<T>().count(e);
  }

  template <typename T> T &getComponent(Entity e) { return getMap<T>().at(e); }

  template <typename T> std::unordered_map<Entity, T> &getMap() {
    static std::unordered_map<Entity, T> map;
    return map;
  }

  template <typename... Components> std::vector<Entity> view() {
    std::vector<Entity> result;

    // Get the first component map to iterate over
    auto &firstMap = getMap<
        typename std::tuple_element<0, std::tuple<Components...>>::type>();

    for (const auto &[entity, _] : firstMap) {
      if ((hasComponent<Components>(entity) && ...)) {
        result.push_back(entity);
      }
    }

    return result;
  }

private:
  Entity nextId = 0;
};
