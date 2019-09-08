/**
 * Health.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Health.hpp"

#include <Game.hpp>

#include <ECS/Systems/System.hpp>
#include <TdManagers/TdCollisionQuadTree/Node.hpp>
#include <TdManagers/TdCollisionQuadTree/QuadTree.hpp>

void Health::update(Game *game, System *system) {
  if (m_curHealth <= 0.0) {
    // if enemy, add to player's money
    if (system->getEnt(m_entID)->has<Attack>() &&
        system->getEnt(m_entID)->get<Attack>()->m_team == Attack::ENEMY) {
      game->m_curMoney += 5.0;
      if (game->m_curMoney > game->m_maxMoney) {
        game->m_curMoney = game->m_maxMoney;
      }
    }
    system->m_collisions.m_qtree->removeEntID(game, system, m_entID);
    system->getEnt(m_entID)->die();
    int id = m_entID;
    system->m_enemies[id] = Entity();
    system->m_allies[id]  = Entity();
  }
}