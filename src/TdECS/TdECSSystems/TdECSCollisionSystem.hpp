#pragma once
/**
 * TdECSCollisionSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>

class TdGame;
class TdECSEntity;
class TdECSSystem;
class TdCollisionQuadTree;

class TdECSCollisionSystem {
 public:
  TdCollisionQuadTree* m_qtree;

  TdECSCollisionSystem();

  ~TdECSCollisionSystem();

  void update(TdGame* game, TdECSSystem* system);

  // currently uses rectangle collisions
  bool isColliding(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2);
  bool isColliding(TdECSSystem* system, TdECSEntity* ent);

  bool willCollide(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2);
  bool willCollide(TdECSSystem* system, TdECSEntity* ent);
};
