/**
 * TdECSSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <TdECS/TdECSSystems/TdCollisionQuadTree/Node.hpp>
#include <TdECS/TdECSSystems/TdCollisionQuadTree/QuadTree.hpp>
#include "System.hpp"
#include "TdECS/Entity.hpp"
#include "SystemPosUtils.hpp"

Entity* System::getEnt(int entID) {
  if (m_enemies.count(entID)) {
    return m_enemies[entID].get();
  } else if (m_allies.count(entID)) {
    return m_allies[entID].get();
  } else {
    return nullptr;
  }
}

void System::addEntity(Game* game, std::unique_ptr<Entity>&& e) {
  int id = e->m_id;
  Entity* ent = e.get();
  if (e->has<Fighter>()) {
    m_enemies[m_nextEntityId++] = std::move(e);
  } else {
    m_allies[m_nextEntityId++] = std::move(e);
  }
  if (!m_collisions.m_qtree->tryAddEntID(game, this, id, ent)) {
    LOG_ERR("Error: FAILED TO ADD ENTITY");
  }
}

void System::update(Game* game, bool updateGraphics) {
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