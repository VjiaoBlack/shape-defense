#pragma once
/**
 * TdCollisionQuadTree.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Node.hpp"

class QuadTree {
 public:
  std::unique_ptr<Node> m_root;

  QuadTree() {
    m_root = std::make_unique<Node>(
        nullptr, Rect(glm::dvec2(-1500, -1500), 4000, 4000));
  }

  bool tryAddEntID(Game *game,
                     System *system,
                     int entID,
                     Entity *ent);
  void removeEntID(Game *game, System *system, int entID);
  void update(Game *game, System *system);
};
