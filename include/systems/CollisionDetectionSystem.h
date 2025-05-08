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
  const float tolerance = 0.05f;

  CollisionInfo XAxisCollision(Entity e1, Entity e2, Registry &registry) {
    CollisionInfo result;
    result.entity1 = e1;
    result.entity2 = e2;
    result.box1 = registry.getComponent<ColliderComponent>(e1).bounds;
    result.box2 = registry.getComponent<ColliderComponent>(e2).bounds;

    if (CheckCollisionBoxes(result.box1, result.box2)) {
      if (result.box1.min.x + tolerance < result.box2.min.x - tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::X;
        result.direction = CollisionInfo::Direction::LEFT;
        return result;
      }
      if (result.box1.max.x - tolerance > result.box2.max.x + tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::X;
        result.direction = CollisionInfo::Direction::RIGHT;
        return result;
      }
    } else {
      result.collided = false;
      result.axis = CollisionInfo::Axis::NONE;
      result.direction = CollisionInfo::Direction::NONE;
    }
    return result;
  }

  CollisionInfo YAxisCollision(Entity e1, Entity e2, Registry &registry) {
    CollisionInfo result;
    result.entity1 = e1;
    result.entity2 = e2;
    result.box1 = registry.getComponent<ColliderComponent>(e1).bounds;
    result.box2 = registry.getComponent<ColliderComponent>(e2).bounds;


    if (CheckCollisionBoxes(result.box1, result.box2)) {
      if (result.box1.min.y - tolerance < result.box2.max.y + tolerance &&
          result.box1.max.y + tolerance > result.box2.max.y + tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::Y;
        result.direction = CollisionInfo::Direction::TOP;
        return result;
      }
      if (result.box1.max.y + tolerance > result.box2.min.y - tolerance &&
          result.box1.min.y - tolerance < result.box2.min.y - tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::Y;
        result.direction = CollisionInfo::Direction::BOTTOM;
        return result;
      }
    } else {
      result.collided = false;
      result.direction = CollisionInfo::Direction::NONE;
    }
    return result;
  }

  CollisionInfo ZAxisCollision(Entity e1, Entity e2, Registry &registry) {
    CollisionInfo result;
    result.entity1 = e1;
    result.entity2 = e2;
    result.box1 = registry.getComponent<ColliderComponent>(e1).bounds;
    result.box2 = registry.getComponent<ColliderComponent>(e2).bounds;

    if (CheckCollisionBoxes(result.box1, result.box2)) {
      if (result.box1.min.z + tolerance < result.box2.min.z - tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::Z;
        result.direction = CollisionInfo::Direction::UP;
        return result;
      }
      if (result.box1.max.z - tolerance > result.box2.max.z + tolerance) {
        result.collided = true;
        result.axis = CollisionInfo::Axis::Z;
        result.direction = CollisionInfo::Direction::DOWN;
        return result;
      }
    } else {
      result.collided = false;
      result.axis = CollisionInfo::Axis::NONE;
      result.direction = CollisionInfo::Direction::NONE;
    }
    return result;
  }
};
