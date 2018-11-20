/**
 * TdECSAttackComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Attack.hpp"
#include <TdECS/TdECSSystems/SystemPosUtils.hpp>
#include <Game.hpp>
#include "TdECS/Entity.hpp"
#include "TdECS/TdECSSystems/TdCollisionQuadTree/QuadTree.hpp"

void Attack::damage(Game *game, System *system) {
  system->getEnt(m_targetEntID)->get<Health>()->m_curHealth -=
      m_damage;
}

void Attack::update(Game *game, System *system) {
  if (m_curCooldown > 0) {
    m_curCooldown -= game->m_deltaTime / 1000.0;
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
    return;
  }

  Entity *myEnt = system->getEnt(m_entID);
  double minDist = -1.0;
  Entity *itEnt = nullptr;

  glm::dvec2 entp = myEnt->getCenterPosition();
  std::vector<Entity *> closeEntsIDs;

  switch (m_target) {
    case 0:  // targets enemies

      system->m_collisions.m_qtree->m_root->getAllWithinRadius(
          system, closeEntsIDs, entp.x, entp.y, 160.0);

      for (auto itTempEnt : closeEntsIDs) {
        auto itIDEnt = itTempEnt;
        double dist = findCenterDistance(myEnt, itIDEnt);

        if (itIDEnt && itIDEnt->has<Fighter>()) {
          if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
            minDist = dist;
            m_targetEntID = itTempEnt->m_id;
            itEnt = itIDEnt;
          }
        }
      }

      //      for (auto &itPair : system->m_entities) {
      //        double dist = findCenterDistance(myEnt, itPair.second.get());
      //
      //        if (itPair.second &&
      //        itPair.second->has<Fighter>()) {
      //          if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
      //            minDist = dist;
      //            m_targetEntID = itPair.first;
      //            itEnt = itPair.second.get();
      //          }
      //        }
      //      }

      if (itEnt) {
        // open fire
        myEnt->get<LaserShooter>()->fire();
        m_curCooldown = m_cooldown;
      }

      break;
    case 1:  // targets allies
      for (auto &itPair : system->m_allies) {
        double dist = findCenterDistance(myEnt, itPair.second.get());

        if (itPair.second && !itPair.second->has<Fighter>()) {
          if (minDist < 0 || dist < minDist) {
            minDist = dist;
            m_targetEntID = itPair.first;
            itEnt = itPair.second.get();
          }
        }
      }

//      if (!system->bubbleWillCollide(itEnt, myEnt)) {
//      if (!system->m_collisions.isColliding(system, itEnt, myEnt)) {
      if (!system->m_collisions.m_collidingIds.count(std::make_pair(std::min(itEnt->m_id,
                                                                             myEnt->m_id),
                                                                    std::max(itEnt->m_id,
                                                                             myEnt->m_id)))) {
        // if closest tower is too far, move towards it
        glm::dvec2 entp = itEnt->getCenterPosition();

        myEnt->get<Pathing>()->move(game, system, entp.x, entp.y);
      } else {
        // otherwise, open fire
        myEnt->get<Pathing>()->stop(game, system);
        myEnt->get<LaserShooter>()->fire();
        m_curCooldown = m_cooldown;
      }
      break;
  }
}
