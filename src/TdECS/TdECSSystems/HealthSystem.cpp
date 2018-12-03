/** 
 * TdECSHealthSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <Game.hpp>
#include "HealthSystem.hpp"
#include "System.hpp"
#include "TdCollisionQuadTree/QuadTree.hpp"

void HealthSystem::update(Game *game, System* system) {
  for (auto c = m_healthComponents.begin(); c != m_healthComponents.end();) {
    if (!(c)->m_alive || c->m_entID == 0) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_healthComponents) {
    if (!c.m_alive || c.m_entID == 0) {
      continue;
    }
    if (c.m_curHealth <= 0.0) {
      // if enemy, add to player's money
      if (system->getEnt(c.m_entID)->get<Attack>()->m_type == Attack::FIGHTER) {
        game->m_curMoney += 5.0;
        if (game->m_curMoney > game->m_maxMoney) {
          game->m_curMoney = game->m_maxMoney;
        }
      }

      system->m_collisions.m_qtree->removeEntID(game, system, c.m_entID);
      system->getEnt(c.m_entID)->die();
      int id = c.m_entID;
      system->m_enemies[id-1] = Entity();
      system->m_allies[id-1] = Entity();
    }
  }
}