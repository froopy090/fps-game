#pragma once
#include "Entity.h"
#include <unordered_map>

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

private:
  Entity nextId = 0;
};
