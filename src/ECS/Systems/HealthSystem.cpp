/** 
 * TdECSHealthSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <Game.hpp>
#include "HealthSystem.hpp"

void HealthSystem::update(Game *game, System* system) {
  for (auto c = m_healthComponents.begin(); c != m_healthComponents.end();) {
    if (!(c)->m_alive) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }
}