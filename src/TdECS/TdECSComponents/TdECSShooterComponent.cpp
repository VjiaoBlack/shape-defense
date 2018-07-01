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

void TdECSShooterComponent::update(TdGame *game) {
  if (m_isShooting) {
    m_curLaserDuration -= 30.0 / 1000.0;
    m_curCooldown -= 30.0 / 1000.0;
    if (m_curLaserDuration < 0) {
      m_curLaserDuration = 0;
      m_targetEnt = nullptr;
      m_isShooting = false;
    }
  } else if (m_curCooldown) {
    m_curCooldown -= 30.0 / 1000.0;
    printf("%f.. %f\n", m_curCooldown, m_cooldown);
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
  } else {
    switch (m_target) {
      case 0:  // targets enemies
        for (auto &ent : game->m_entitySystem->m_entities) {
          // if it's a fighter (assume all fighters are enemies for now
          // TODO: assumption
          if (ent->has<TdECSFighterComponent>()) {
            // and if it's close enough
            double entX = ent->get<TdECSPositionComponent>()->m_x;
            double entY = ent->get<TdECSPositionComponent>()->m_y;

            entX -= m_ent->get<TdECSTilePositionComponent>()->m_x * 17 +
                    K_DISPLAY_SIZE_X / 2 - 8;
            entY -= m_ent->get<TdECSTilePositionComponent>()->m_y * 17 +
                    K_DISPLAY_SIZE_Y / 2 - 8;

            if (entX * entX + entY * entY < 150.0 * 150.0) {
              // attack it
              m_isShooting = true;
              m_curLaserDuration = m_laserDuration;
              m_curCooldown = m_cooldown;
              m_targetEnt = ent.get();
            }
          }
        }

        break;
      case 1:
        break;
    }
  }
}
