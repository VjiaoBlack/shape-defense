/** 
 * TdECSPhysicsSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "PhysicsSystem.hpp"
#include "System.hpp"
#include "../Entity.hpp"

void PhysicsSystem::update(Game *game, System* system) {
  for (auto c = m_physicsComponents.begin(); c != m_physicsComponents.end();) {
    if (!(c)->m_alive || c->m_entID == 0) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_physicsComponents) {
    if (!c.m_alive || c.m_entID == 0) {
      continue;
    }
    system->getEnt(c.m_entID)->get<Position>()->m_p += c.m_v;
  }
}