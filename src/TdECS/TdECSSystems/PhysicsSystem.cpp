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
    if (!(*c)->m_alive) {
      c = m_physicsComponents.erase(c);
    } else {
      (*c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_physicsComponents) {
    system->getEnt(c->m_entID)->get<Position>()->m_p += c->m_v;
  }

  // don't need to update position components?
}