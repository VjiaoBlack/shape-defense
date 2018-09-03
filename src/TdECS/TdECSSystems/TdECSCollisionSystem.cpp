/** 
 * TdECSCollisionSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSCollisionSystem.hpp"

#include <TdECS/TdECSSystems/TdCollisionQuadTree/TdCollisionQuadTreeNode.hpp>
#include "TdCollisionQuadTree/TdCollisionQuadTree.hpp"

TdECSCollisionSystem::TdECSCollisionSystem() {
  m_qtree = new TdCollisionQuadTree();
}

TdECSCollisionSystem::~TdECSCollisionSystem() {
  delete m_qtree;
}

void TdECSCollisionSystem::update(TdGame* game, TdECSSystem* system) {
  m_qtree->update(game, system);
}

bool TdECSCollisionSystem::isColliding(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2) {
  if (!ent1 || !ent2) {
    std::cerr << "Collision system passed a Null ent." << std::endl;
    return true;
  }

  glm::dvec2 ent1p = ent1->getPosition();
  double ent1x2 = ent1p.x + ent1->get<TdECSShapeComponent>()->m_width;
  double ent1y2 = ent1p.y + ent1->get<TdECSShapeComponent>()->m_height;

  glm::dvec2 ent2p = ent2->getPosition();
  double ent2x2 = ent2p.x + ent2->get<TdECSShapeComponent>()->m_width;
  double ent2y2 = ent2p.y + ent2->get<TdECSShapeComponent>()->m_height;

  return ent1p.x < ent2x2 && ent1x2 > ent2p.x && ent1p.y < ent2y2 &&
      ent1y2 > ent2p.y;
}

bool TdECSCollisionSystem::isColliding(TdECSSystem* system, TdECSEntity* ent) {
  std::list<TdCollisionQuadTreeNode*> nearbyNodes;
  m_qtree->m_root->getContainingNode(system, ent->m_id)
      ->getAdjacentNodes(nearbyNodes);

  for (auto n : nearbyNodes) {
    for (auto e : n->m_ents) {
      if (ent->m_id != e.first && this->isColliding(system, ent, e.second)) {
        return true;
      }
    }
  }

  return false;
}