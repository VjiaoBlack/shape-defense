/**
 * TdECSAttackComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSAttackComponent.hpp"
#include "../TdECSEntity.hpp"

void TdECSAttackComponent::damage(TdGame *game, TdECSSystem *system) {
  system->m_entities[m_targetEntID]->get<TdECSHealthComponent>()->m_curHealth -=
      m_damage;
}

void TdECSAttackComponent::update(TdGame *game, TdECSSystem *system) {
  if (m_curCooldown > 0) {
    m_curCooldown -= 30.0 / 1000.0;
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
    return;
  }

  TdECSEntity *myEnt = system->m_entities[m_entID].get();
  double minDist = -1.0;
  TdECSEntity *itEnt = nullptr;
  switch (m_target) {
    case 0:  // targets enemies
      for (auto &itPair : system->m_entities) {
        double dist = findCenterDistance(myEnt, itPair.second.get());

        if (itPair.second && itPair.second->has<TdECSFighterComponent>()) {
          if (dist < 150.0 && (minDist < 0 || dist < minDist)) {
            minDist = dist;
            m_targetEntID = itPair.first;
            itEnt = itPair.second.get();
          }
        }
      }

      if (itEnt) {
        // open fire
        myEnt->get<TdECSLaserShooterComponent>()->fire();
        m_curCooldown = m_cooldown;
      }

      break;
    case 1:  // targets allies
      for (auto &itPair : system->m_entities) {
        double dist = findCenterDistance(myEnt, itPair.second.get());

        if (itPair.second && itPair.second->has<TdECSShooterComponent>()) {
          if (minDist < 0 || dist < minDist) {
            minDist = dist;
            m_targetEntID = itPair.first;
            itEnt = itPair.second.get();
          }
        }
      }

      if (minDist > 60.0) {
        // if closest tower is too far, move towards it
        double entXDist, entYDist;
        std::tie(entXDist, entYDist) = findCenterDisplacement(myEnt, itEnt);

        myEnt->get<TdECSPhysicsComponent>()->m_vx = 2.0 * entXDist / minDist;
        myEnt->get<TdECSPhysicsComponent>()->m_vy = 2.0 * entYDist / minDist;
      } else {
        // otherwise, open fire
        myEnt->get<TdECSPhysicsComponent>()->m_vx = 0.0;
        myEnt->get<TdECSPhysicsComponent>()->m_vy = 0.0;
        myEnt->get<TdECSLaserShooterComponent>()->fire();
        m_curCooldown = m_cooldown;
      }
      break;
  }
}
