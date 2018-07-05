/**
 * TdECSShooterComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSShooterComponent.hpp"
#include <TdGame.hpp>
#include "../TdECSEntity.hpp"

void TdECSShooterComponent::update(TdGame *game, TdECSSystem *system) {
  if (m_isShooting) {
    if (!system->m_entities.count(m_targetEntId)) {
      m_isShooting = false;
      m_targetEntId = -1;
    } else {
      m_curLaserDuration -= 30.0 / 1000.0;
      m_curCooldown -= 30.0 / 1000.0;
      if (m_curLaserDuration < 0) {
        (system->m_entities[m_targetEntId])->get<TdECSHealthComponent>()->m_health -= m_damage;
        m_curLaserDuration = 0;
        m_targetEntId = -1;
        m_isShooting = false;
      }
    }
  } else if (m_curCooldown) {
    m_curCooldown -= 30.0 / 1000.0;
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
  } else {
    switch (m_target) {
      case 0:  // targets enemies
        for (auto &ent_pair : game->m_entitySystem->m_entities) {
          // if it's a fighter (assume all fighters are enemies for now
          // TODO: assumption
          if (ent_pair.second && ent_pair.second->has<TdECSFighterComponent>()) {
            // and if it's close enough
            double itEntX, itEntY;
            std::tie(itEntX, itEntY) = getCenterPosition(ent_pair.second.get());

            double entX, entY;
            std::tie(entX, entY) = getCenterPosition(system->m_entities[m_entId].get());

            entX -= itEntX;
            entY -= itEntY;

            if (entX * entX + entY * entY < 150.0 * 150.0) {
              // attack it
              m_isShooting = true;
              m_curLaserDuration = m_laserDuration;
              m_curCooldown = m_cooldown;
              m_targetEntId = ent_pair.first;
              break;
            }
          }
        }

        break;
      case 1:
        break;
    }
  }
}
