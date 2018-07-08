#pragma once
/**
 * TdECSCollisionSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdCollisionQuadTree/TdCollisionQuadTree.hpp"

class TdECSCollisionSystem {
 public:
  std::unique_ptr<TdCollisionQuadTree> m_qtree;

  TdECSCollisionSystem() {
    m_qtree = std::make_unique<TdCollisionQuadTree>();
  }

  void update(TdGame* game, TdECSSystem* system) {
    m_qtree->update(game, system);
  }
};
