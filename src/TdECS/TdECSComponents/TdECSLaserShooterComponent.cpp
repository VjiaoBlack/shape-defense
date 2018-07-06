/** 
 * TdECSLaserShooterComponent.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSLaserShooterComponent.hpp"
#include "TdECSShooterComponent.hpp"
#include <TdGame.hpp>
#include "../TdECSEntity.hpp"
#include "TdECSAttackComponent.hpp"

void TdECSLaserShooterComponent::update(TdGame *game, TdECSSystem *system) {
  auto& ent = system->m_entities[m_entID];
  int targetEntID = ent->get<TdECSAttackComponent>()->m_targetEntID;

  if (m_isShooting) {
    if (!system->m_entities.count(targetEntID)) {
      m_isShooting = false;
      ent->get<TdECSAttackComponent>()->m_targetEntID = -1;
    } else {
      m_curLaserDuration -= game->m_deltaTime / 1000.0;
      if (m_curLaserDuration < 0) {
        m_curLaserDuration = 0;
        ent->get<TdECSAttackComponent>()->damage(game, system);
        ent->get<TdECSAttackComponent>()->m_targetEntID = -1;
        m_isShooting = false;
      }
    }
  }
}
