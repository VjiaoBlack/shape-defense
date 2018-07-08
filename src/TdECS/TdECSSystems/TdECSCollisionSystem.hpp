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
class TdECSSystem;
class TdCollisionQuadTree;

class TdECSCollisionSystem {
 public:
  TdCollisionQuadTree* m_qtree;

  TdECSCollisionSystem();

  ~TdECSCollisionSystem();

  void update(TdGame* game, TdECSSystem* system);
};
