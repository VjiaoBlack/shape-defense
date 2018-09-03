/**
 * TdECSSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <TdECS/TdECSSystems/TdCollisionQuadTree/TdCollisionQuadTreeNode.hpp>
#include <TdECS/TdECSSystems/TdCollisionQuadTree/TdCollisionQuadTree.hpp>
#include "TdECSSystem.hpp"
#include "../TdECSEntity.hpp"
#include "TdECSSystemPosUtils.hpp"

TdECSEntity* TdECSSystem::getEnt(int entID) {
  if (m_enemies.count(entID)) {
    return m_enemies[entID].get();
  } else if (m_allies.count(entID)) {
    return m_allies[entID].get();
  } else {
    return nullptr;
  }
}

bool TdECSSystem::isColliding(TdECSEntity* ent1, TdECSEntity* ent2) {
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

bool TdECSSystem::isColliding(TdECSEntity* ent) {
  std::list<TdCollisionQuadTreeNode*> nearbyNodes;
  m_collisions.m_qtree->m_root->getContainingNode(this, ent->m_id)
      ->getAdjacentNodes(nearbyNodes);

  for (auto n : nearbyNodes) {
    for (auto e : n->m_ents) {
      if (ent->m_id != e.first && this->isColliding(ent, e.second)) {
        return true;
      }
    }
  }

  return false;
}

void TdECSSystem::addEntity(TdGame* game, std::unique_ptr<TdECSEntity>&& e) {
  int id = e->m_id;
  TdECSEntity* ent = e.get();
  if (e->has<TdECSFighterComponent>()) {
    m_enemies[m_nextEntityId++] = std::move(e);
  } else {
    m_allies[m_nextEntityId++] = std::move(e);
  }
  if (!m_collisions.m_qtree->tryAddEntID(game, this, id, ent)) {
    std::cerr << "Error: FAILED TO ADD ENTITY" << std::endl;
  }
}

void TdECSSystem::update(TdGame* game, bool updateGraphics) {
  m_health.update(game, this);
  m_planning.update(game, this);
  m_physics.update(game, this);

  if (updateGraphics) {
    m_graphics.update(game, this);
  }

  auto entMapList = this->getEntityMaps();
  for (auto map : entMapList) {
    for (auto c = map->begin(); c != map->end();) {
      if ((*c).second->m_dead) {
        c = map->erase(c);
      } else {
        c++;
      }
    }
  }
  m_collisions.update(game, this);

  printf("numEntities: %lu\n", m_allies.size() + m_enemies.size());
}