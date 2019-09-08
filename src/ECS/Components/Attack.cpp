/**
 * Attack.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Attack.hpp"

#include <Game.hpp>

#include <ECS/Systems/System.hpp>
#include <ECS/Systems/SystemPosUtils.hpp>
#include <TdManagers/TdCollisionQuadTree/Node.hpp>
#include <TdManagers/TdCollisionQuadTree/QuadTree.hpp>

void Attack::update(Game *game, System *system) {
  if (!m_alive) {
    return;
  }
  if (m_curCooldown > 0) {
    m_curCooldown -= game->m_deltaTime / 1000.0;
    if (m_curCooldown < 0) {
      m_curCooldown = 0;
    }
    return;
  }

  Entity *myEnt = system->getEnt(m_entID);

  if (!myEnt || !myEnt->m_alive) {
    return;
  }
  double minDist = -1.0;
  Entity *itEnt  = nullptr;

  glm::dvec2            entp = myEnt->getCenterPosition();
  std::vector<Entity *> closeEntsIDs;

  switch (m_team) {
    case Attack::ALLIED:  // targets enemies
      system->m_collisions.m_qtree->m_root->getAllWithinRadius(
          system, closeEntsIDs, entp.x, entp.y, 160.0);

      for (auto itTempEnt : closeEntsIDs) {
        if (!itTempEnt || !itTempEnt->m_alive) {
          continue;
        }

        auto   itIDEnt = itTempEnt;
        double dist    = findCenterDistance(*myEnt, *itIDEnt);

        if (itIDEnt &&
            itIDEnt->has<Attack>() &&
            itIDEnt->get<Attack>()->m_team == Attack::ENEMY) {
          if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
            minDist       = dist;
            m_targetEntID = itTempEnt->m_id;
            itEnt         = itIDEnt;
          }
        }
      }

      if (itEnt) {
        // open fire
        myEnt->get<LaserShooter>()->fire();
        m_curCooldown = m_cooldown;
      }

      break;
    case Attack::ENEMY:  // targets allies
      for (auto &itPair : system->m_allies) {
        if (!itPair.m_alive) {
          continue;
        }

        double dist = findCenterDistance(*myEnt, itPair);

        if (minDist < 0 || dist < minDist) {
          minDist       = dist;
          m_targetEntID = itPair.m_id;
          itEnt         = &itPair;
        }
      }
      if (!itEnt) {
        return;
      }
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