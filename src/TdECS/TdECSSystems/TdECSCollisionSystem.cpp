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

  // getAdjacentNodes is faulty.
//  m_qtree->m_root->getContainingNode(system, ent->m_id)
//      ->getAdjacentNodes(nearbyNodes);

//  for (auto n : nearbyNodes) {
//    for (auto e : n->m_ents) {
//      if (ent->m_id != e.first && this->isColliding(system, ent, e.second)) {
//        return true;
//      }
//    }
//  }

  for (auto& e : system->m_enemies) {
    if (ent->m_id != e.first && this->isColliding(system, ent, e.second.get())) {
      return true;
    }
  }

  for (auto& e : system->m_allies) {
    if (ent->m_id != e.first && this->isColliding(system, ent, e.second.get())) {
      return true;
    }
  }


  return false;
}

bool TdECSCollisionSystem::willCollide(TdECSSystem* system, TdECSEntity* ent1, TdECSEntity* ent2) {
  if (!ent1 || !ent2) {
    std::cerr << "Collision system passed a Null ent." << std::endl;
    return true;
  }

  double v1x = 0.0;
  double v1y = 0.0;
  double v2x = 0.0;
  double v2y = 0.0;

  bool moving1 = false;
  bool moving2 = false;

  if (ent1->has<TdECSPhysicsComponent>()) {
    moving1 = true;
    v1x = ent1->get<TdECSPhysicsComponent>()->m_vx;
    v1y = ent1->get<TdECSPhysicsComponent>()->m_vy;
  }
  if (ent2->has<TdECSPhysicsComponent>()) {
    moving2 = true;
    v2x = ent2->get<TdECSPhysicsComponent>()->m_vx;
    v2y = ent2->get<TdECSPhysicsComponent>()->m_vy;
  }
  glm::dvec2 ent1p = ent1->getPosition();
  glm::dvec2 ent2p = ent2->getPosition();

  double ent1x2 = v1x + ent1p.x + ent1->get<TdECSShapeComponent>()->m_width;
  double ent1y2 = v1y + ent1p.y + ent1->get<TdECSShapeComponent>()->m_height;

  double ent2x2 = v2x + ent2p.x + ent2->get<TdECSShapeComponent>()->m_width;
  double ent2y2 = v2y + ent2p.y + ent2->get<TdECSShapeComponent>()->m_height;

  bool willCollideBothFuture = ent1p.x < ent2x2 && ent1x2 > ent2p.x && ent1p.y < ent2y2 &&
      ent1y2 > ent2p.y;

  bool willCollide1Future = false;
  bool willCollide2Future = false;

  if (moving1) {
    ent1x2 = v1x + ent1p.x + ent1->get<TdECSShapeComponent>()->m_width;
    ent1y2 = v1y + ent1p.y + ent1->get<TdECSShapeComponent>()->m_height;

    ent2x2 = ent2p.x + ent2->get<TdECSShapeComponent>()->m_width;
    ent2y2 = ent2p.y + ent2->get<TdECSShapeComponent>()->m_height;

    willCollide1Future = ent1p.x < ent2x2 && ent1x2 > ent2p.x && ent1p.y < ent2y2 &&
        ent1y2 > ent2p.y;
  }

  if (moving2) {
    ent1x2 = ent1p.x + ent1->get<TdECSShapeComponent>()->m_width;
    ent1y2 = ent1p.y + ent1->get<TdECSShapeComponent>()->m_height;

    ent2x2 = v2x + ent2p.x + ent2->get<TdECSShapeComponent>()->m_width;
    ent2y2 = v2y + ent2p.y + ent2->get<TdECSShapeComponent>()->m_height;

    willCollide2Future = ent1p.x < ent2x2 && ent1x2 > ent2p.x && ent1p.y < ent2y2 &&
        ent1y2 > ent2p.y;
  }

  return willCollideBothFuture || willCollide1Future || willCollide2Future;
}

bool TdECSCollisionSystem::willCollide(TdECSSystem* system, TdECSEntity* ent) {
  // getAdjacentNodes is faulty.
//  std::list<TdCollisionQuadTreeNode*> nearbyNodes;
//  m_qtree->m_root->getContainingNode(system, ent->m_id)
//      ->getAdjacentNodes(nearbyNodes);
//
//  for (auto n : nearbyNodes) {
//    for (auto e : n->m_ents) {
//      if (ent->m_id != e.first && this->willCollide(system, ent, e.second)) {
//        return true;
//      }
//    }
//  }

  for (auto& e : system->m_enemies) {
    if (ent->m_id != e.first && this->willCollide(system, ent, e.second.get())) {
      return true;
    }
  }

  for (auto& e : system->m_allies) {
    if (ent->m_id != e.first && this->willCollide(system, ent, e.second.get())) {
      return true;
    }
  }

  return false;
}