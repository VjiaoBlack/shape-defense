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

void TdECSSystem::addEntity(TdGame* game, std::unique_ptr<TdECSEntity>&& e) {
  int id = e->m_id;
  TdECSEntity* ent = e.get();
  if (e->has<TdECSFighterComponent>()) {
    m_enemies[m_nextEntityId++] = std::move(e);
  } else {
    m_allies[m_nextEntityId++] = std::move(e);
  }
  if (!m_collisions.m_qtree->tryAddEntID(game, this, id, ent)) {
    LOG_ERR("Error: FAILED TO ADD ENTITY");
  }
}

void TdECSSystem::update(TdGame* game, bool updateGraphics) {
  m_health.update(game, this);
  m_planning.update(game, this);
  m_collisions.update(game, this);
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

  LOG_VRB("numEntities: %lu\n", m_allies.size() + m_enemies.size());
}