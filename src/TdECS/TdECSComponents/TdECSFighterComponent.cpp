/**
 * TdECSFighterComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSFighterComponent.hpp"
#include "../TdECSEntity.hpp"
#include "TdGame.hpp"

void TdECSFighterComponent::update(TdGame *game, TdECSSystem *system) {
  if (!m_isShooting && m_targetEntId >= 0) {
    double minDist = -1.0;
    bool enemyFound = false;
    for (auto &ent_pair : game->m_entitySystem->m_entities) {
      // if it's a shooter (assume all shooters are allies for now
      // TODO: assumption
      if (ent_pair.second && ent_pair.second->has<TdECSShooterComponent>()) {
        // and if it's close enough
        double itEntX, itEntY;
        std::tie(itEntX, itEntY) = getCenterPosition(ent_pair.second.get());

        double entX, entY;
        std::tie(entX, entY) = getCenterPosition(system->m_entities[m_entId].get());

        entX -= itEntX;
        entY -= itEntY;

        double dist = sqrt(entX * entX + entY * entY);
        if (minDist < 0 || dist < minDist) {
          minDist = dist;
          m_targetEntId = ent_pair.first;
          enemyFound = true;
        }
      }
    }

    if (!enemyFound) {
      m_targetEntId = -1;
      return;
    }

    double targetEntX, targetEntY;
    std::tie(targetEntX, targetEntY) =
        getCenterPosition(system->m_entities[m_targetEntId].get());

    double entX, entY;
    std::tie(entX, entY) = getCenterPosition(system->m_entities[m_entId].get());

    entX = targetEntX - entX;
    entY = targetEntY - entY;

    double dist = sqrt(entX * entX + entY * entY);

    //     go towards it if its far
    if (dist > 60.0) {
      // move towards it
      // TODO: make planning component
      system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vx =
          2.0 * entX / dist;
      system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vy =
          2.0 * entY / dist;
    } else {
      // stop
      // TODO: planning component
      system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vx = 0.0;
      system->m_entities[m_entId]->get<TdECSPhysicsComponent>()->m_vy = 0.0;
      // start fighting
      m_isShooting = true;
      m_curCooldown = m_cooldown;
      m_curLaserDuration = m_laserDuration;
    }

  } else if (m_isShooting) {
    if (!system->m_entities.count(m_targetEntId)) {
      m_isShooting = false;
      m_targetEntId = -1;
    } else {
      m_curLaserDuration -= 30.0 / 1000.0;
      m_curCooldown -= 30.0 / 1000.0;
      if (m_curLaserDuration < 0) {
        (system->m_entities[m_targetEntId])
            ->get<TdECSHealthComponent>()
            ->m_health -= m_damage;
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
      case 0:
        break;
      case 1:  // targets allies
        double minDist = -1.0;
        for (auto &ent_pair : game->m_entitySystem->m_entities) {
          // if it's a shooter (assume all shooters are allies for now
          // TODO: assumption
          if (ent_pair.second &&
              ent_pair.second->has<TdECSShooterComponent>()) {
            // and if it's close enough
            double itEntX, itEntY;
            std::tie(itEntX, itEntY) = getCenterPosition(ent_pair.second.get());

            double entX, entY;
            std::tie(entX, entY) = getCenterPosition(system->m_entities[m_entId].get());

            entX -= itEntX;
            entY -= itEntY;

            double dist = sqrt(entX * entX + entY * entY);
            if (minDist < 0 || dist < minDist) {
              minDist = dist;
              m_targetEntId = ent_pair.first;
            }
          }
        }
        break;
    }
  }
}