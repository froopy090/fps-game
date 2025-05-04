#pragma once

#include <Component.h>
#include <Registry.h>
#include <iostream>
#include <shared/SharedResources.h>
#include <systems/System.h>

class CollisionDetectionSystem : public System {
public:
  void Update(Registry &registry) override;

private:
  CollisionInfo YAxisCollision(Entity e1, Entity e2, Registry &registry) {
    float tolerance = 0.05f;
    CollisionInfo result;
    result.entity1 = e1;
    result.entity2 = e2;
    result.box1 = registry.getComponent<ColliderComponent>(e1).bounds;
    result.box2 = registry.getComponent<ColliderComponent>(e2).bounds;
    // First, update the collision boxes' position

    if (CheckCollisionBoxes(result.box1, result.box2)) {
      result.collided = true;
      result.axis = CollisionInfo::Axis::Y;
      // std::cout << "colliding" << std::endl;
      if (result.box1.min.y - tolerance <= result.box2.max.y + tolerance &&
          result.box1.max.y + tolerance > result.box2.max.y + tolerance) {
        result.direction = CollisionInfo::Direction::TOP;
        // std::cout << "TOP collision" << std::endl;
        return result;
      }
      if (result.box1.max.y + tolerance >= result.box2.min.y - tolerance &&
          result.box1.min.y - tolerance < result.box2.min.y - tolerance) {
        result.direction = CollisionInfo::Direction::BOTTOM;
        // std::cout << "BOTTOM" << std::endl;
        return result;
      }
    } else {
      result.collided = false;
      result.direction = CollisionInfo::Direction::NONE;
      return result;
    }
    return result;
  }
};
