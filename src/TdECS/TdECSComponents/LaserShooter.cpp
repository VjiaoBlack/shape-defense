/** 
 * TdECSLaserShooterComponent.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "LaserShooter.hpp"
#include <Game.hpp>
#include "TdECS/Entity.hpp"
#include "Attack.hpp"

void LaserShooter::update(Game *game, System *system) {
  auto ent = system->getEnt(m_entID);
  int targetEntID = ent->get<Attack>()->m_targetEntID;

  if (m_isShooting) {
    if (!system->getEnt(targetEntID)) {
      m_isShooting = false;
      ent->get<Attack>()->m_targetEntID = -1;
    } else {
      m_curLaserDuration -= game->m_deltaTime / 1000.0;
      if (m_curLaserDuration < 0) {
        m_curLaserDuration = 0;
        ent->get<Attack>()->damage(game, system);
        ent->get<Attack>()->m_targetEntID = -1;
        m_isShooting = false;
      }
    }
  }
}
