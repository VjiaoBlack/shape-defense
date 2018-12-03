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
  if (m_enemies[entID-1].m_id > 0) {
    return &m_enemies[entID-1];
  } else if (m_allies[entID-1].m_id > 0) {
    return &m_allies[entID-1];
  } else {
    return nullptr;
  }
}

void System::addEntity(Game *game, Entity e) {
  int id = e.m_id; // already set correctly.
  if (e.has<Attack>() &&
      e.get<Attack>()->m_type ==
          Attack::FIGHTER) {
    m_enemies[id-1] = std::move(e);
  } else {
    m_allies[id-1] = std::move(e);
  }
  if (!m_collisions.m_qtree->tryAddEntID(game, this, id)) {
    LOG_ERR("Error: FAILED TO ADD ENTITY");
  }
}

void System::update(Game* game, bool updateGraphics) {
  m_health.update(game, this);
  m_collisions.update(game, this);
  m_planning.update(game, this);
  m_physics.update(game, this);

  if (updateGraphics) {
    m_graphics.update(game, this);
  }

  // TODO is this necessary
//  auto entMapList = this->getEntityMaps();
//  for (auto map : entMapList) {
//    for (auto c = map->begin(); c != map->end();) {
//      if (!c->m_alive) {
////        printf("ERASE ENT %d FROM MAP\n", c->first);
////        c = map->erase(c);
//      } else {
//        c++;
//      }
//    }
//  }

//  LOG_ERR("numEntities: %lu", m_allies.size() + m_enemies.size());
}