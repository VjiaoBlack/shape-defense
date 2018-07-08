/**
 * TdECSAttackComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSAttackComponent.hpp"
#include <TdGame.hpp>
#include <TdECS/TdECSSystems/TdECSSystemPosUtils.hpp>
#include "../TdECSEntity.hpp"

void TdECSAttackComponent::damage(TdGame *game, TdECSSystem *system) {
  system->getEnt(m_targetEntID)->get<TdECSHealthComponent>()->m_curHealth -=
      m_damage;
}

void TdECSAttackComponent::update(TdGame *game, TdECSSystem *system) {
  if (m_curCooldown > 0) {
    m_curCooldown -= game->m_deltaTime / 1000.0;
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
    return;
  }

  TdECSEntity *myEnt = system->getEnt(m_entID);
  double minDist = -1.0;
  TdECSEntity *itEnt = nullptr;

  glm::dvec2 entp = getCenterPosition(myEnt);
  std::unordered_map<int, TdECSEntity *> closeEntsIDs;

  switch (m_target) {
    case 0:  // targets enemies

      system->m_collisions.m_qtree->m_root->getAllWithinRadius(
          system, closeEntsIDs, entp.x, entp.y, 160.0);

      for (auto itID : closeEntsIDs) {
        auto itIDEnt = itID.second;
        double dist = findCenterDistance(myEnt, itIDEnt);

        if (itIDEnt && itIDEnt->has<TdECSFighterComponent>()) {
          if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
            minDist = dist;
            m_targetEntID = itID.first;
            itEnt = itIDEnt;
          }
        }
      }

      //      for (auto &itPair : system->m_entities) {
      //        double dist = findCenterDistance(myEnt, itPair.second.get());
      //
      //        if (itPair.second &&
      //        itPair.second->has<TdECSFighterComponent>()) {
      //          if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
      //            minDist = dist;
      //            m_targetEntID = itPair.first;
      //            itEnt = itPair.second.get();
      //          }
      //        }
      //      }

      if (itEnt) {
        // open fire
        myEnt->get<TdECSLaserShooterComponent>()->fire();
        m_curCooldown = m_cooldown;
      }

      break;
    case 1:  // targets allies
      for (auto &itPair : system->m_allies) {
        double dist = findCenterDistance(myEnt, itPair.second.get());

        if (itPair.second && !itPair.second->has<TdECSFighterComponent>()) {
          if (minDist < 0 || dist < minDist) {
            minDist = dist;
            m_targetEntID = itPair.first;
            itEnt = itPair.second.get();
          }
        }
      }

      if (!system->bubbleWillCollide(itEnt, myEnt)) {
        // if closest tower is too far, move towards it
        glm::dvec2 entp = getCenterPosition(itEnt);

        myEnt->get<TdECSPathingComponent>()->move(game, system, entp.x, entp.y);
      } else {
        // otherwise, open fire
        myEnt->get<TdECSPathingComponent>()->stop(game, system);
        myEnt->get<TdECSLaserShooterComponent>()->fire();
        m_curCooldown = m_cooldown;
      }
      break;
  }
}
