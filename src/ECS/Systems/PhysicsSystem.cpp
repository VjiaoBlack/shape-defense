/** 
 * TdECSPhysicsSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "PhysicsSystem.hpp"

void PhysicsSystem::update(Game *game, System* system) {
  for (auto c = m_physicsComponents.begin(); c != m_physicsComponents.end();) {
    if (!(c)->m_alive) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }
}