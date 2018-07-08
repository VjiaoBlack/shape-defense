#pragma once
/**
 * TdCollisionQuadTree.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdCollisionQuadTreeNode.hpp"

class TdCollisionQuadTree {
 public:
  std::unique_ptr<TdCollisionQuadTreeNode> m_root;

  TdCollisionQuadTree() {
    m_root = std::make_unique<TdCollisionQuadTreeNode>(
        nullptr, TdECSRect(glm::dvec2(-1500, -1500), 4000, 4000));
  }

  bool tryAddEntID(TdGame *game, TdECSSystem *system, int entID);
  void removeEntID(TdGame *game, TdECSSystem *system, int entID);
  void update(TdGame *game, TdECSSystem *system);
};
