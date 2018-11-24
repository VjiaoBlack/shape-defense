/** 
 * TdECSHealthSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "HealthSystem.hpp"

#include "System.hpp"
#include "TdCollisionQuadTree/QuadTree.hpp"

void HealthSystem::update(Game *game, System* system) {
  for (auto c = m_healthComponents.begin(); c != m_healthComponents.end();) {
    if (!(*c)->m_alive) {
      c = m_healthComponents.erase(c);
    } else {
      (*c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_healthComponents) {
    if (c->m_curHealth <= 0.0) {
      system->m_collisions.m_qtree->removeEntID(game, system, c->m_entID);
      system->getEnt(c->m_entID)->die();
    }
  }

}