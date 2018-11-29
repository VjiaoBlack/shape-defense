/** 
 * TdECSPlanningSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdCollisionQuadTree/Node.hpp"
#include "TdCollisionQuadTree/QuadTree.hpp"


#include <Game.hpp>
#include "PlanningSystem.hpp"
#include "../Entity.hpp"
#include "SystemPosUtils.hpp"

void Attack::damage(Game *game, System *system) {
  system->getEnt(m_targetEntID)->get<Health>()->m_curHealth -=
      m_damage;
}
void Pathing::move(Game* game, System* system, double x,
                   double y) {
  m_goalxy = glm::dvec2(x, y);
  auto myEnt = system->getEnt(m_entID);
  glm::dvec2 entxy = myEnt->getCenterPosition();

  glm::dvec2 entdistxy = m_goalxy - entxy;
  double dist = sqrt(glm::dot(entdistxy, entdistxy));

  myEnt->get<Physics>()->m_v =
      60.0 * game->m_deltaTime * entdistxy / (dist * 1000.0);
  m_isMoving = true;
}

void Pathing::stop(Game* game, System* system) {
  m_isMoving = false;

  system->getEnt(m_entID)->get<Physics>()->m_v = glm::vec2(0.0);
}

void PlanningSystem::update(Game *game, System* system) {
  for (auto c = m_attackComponents.begin(); c != m_attackComponents.end();) {
    if (!(c)->m_alive || c->m_entID == 0) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto &c : m_attackComponents) {

    if (!c.m_alive || c.m_entID == 0) {
      continue;
    }
    if (c.m_curCooldown > 0) {
      c.m_curCooldown -= game->m_deltaTime / 1000.0;
      if (c.m_curCooldown < 0) {
        c.m_curCooldown = 0;
      }
      continue;
    }

    Entity *myEnt = system->getEnt(c.m_entID);

    if (!myEnt || !myEnt->m_alive) {
      continue;
    }
    double minDist = -1.0;
    Entity *itEnt = nullptr;

    glm::dvec2 entp = myEnt->getCenterPosition();
    std::vector<Entity *> closeEntsIDs;

    switch (c.m_target) {
      case 0:  // targets enemies

        system->m_collisions.m_qtree->m_root->getAllWithinRadius(
            system, closeEntsIDs, entp.x, entp.y, 160.0);

        for (auto itTempEnt : closeEntsIDs) {
          if (!itTempEnt || !itTempEnt->m_alive) {
            continue;
          }

          auto itIDEnt = itTempEnt;
          double dist = findCenterDistance(myEnt, itIDEnt);

          if (itIDEnt &&
              itIDEnt->has<Attack>() &&
              itIDEnt->get<Attack>()->m_type == Attack::FIGHTER) {
            if (dist < 160.0 && (minDist < 0 || dist < minDist)) {
              minDist = dist;
              c.m_targetEntID = itTempEnt->m_id;
              itEnt = itIDEnt;
            }
          }
        }

        if (itEnt) {
          // open fire
          myEnt->get<LaserShooter>()->fire();
          c.m_curCooldown = c.m_cooldown;
        }

        break;
      case 1:  // targets allies
        for (auto &itPair : system->m_allies) {
          if (!itPair.second || !itPair.second->m_alive) {
            continue;
          }

          double dist = findCenterDistance(myEnt, itPair.second.get());

          if (itPair.second &&
              itPair.second->has<Attack>() &&
              itPair.second->get<Attack>()->m_type == Attack::SHOOTER) {
            if (minDist < 0 || dist < minDist) {
              minDist = dist;
              c.m_targetEntID = itPair.first;
              itEnt = itPair.second.get();
            }
          }
        }
        if (!itEnt) {
          continue;
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
          c.m_curCooldown = c.m_cooldown;
        }
        break;
    }
  }




  for (auto c = m_laserComponents.begin(); c != m_laserComponents.end();) {
    if (!(c)->m_alive || c->m_entID == 0) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }
  for (auto &comp : m_laserComponents) {
    if (!comp.m_alive || comp.m_entID == 0) {
      continue;
    }
    auto ent = system->getEnt(comp.m_entID);
    int targetEntID = ent->get<Attack>()->m_targetEntID;

    if (comp.m_isShooting) {
      if (!system->getEnt(targetEntID)) {
        comp.m_isShooting = false;
        ent->get<Attack>()->m_targetEntID = -1;
      } else {
        comp.m_curLaserDuration -= game->m_deltaTime / 1000.0;
        if (comp.m_curLaserDuration < 0) {
          comp.m_curLaserDuration = 0;
          ent->get<Attack>()->damage(game, system);
          ent->get<Attack>()->m_targetEntID = -1;
          comp.m_isShooting = false;
        }
      }
    }
  }





  for (auto c = m_pathingComponents.begin(); c != m_pathingComponents.end();) {
    if (!(c)->m_alive || c->m_entID == 0) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_pathingComponents) {
    if (!c.m_alive || c.m_entID == 0) {
      continue;
    }
    if (c.m_isMoving) {
      // find collision
      auto myEnt = system->getEnt(c.m_entID);

      bool willCollide = system->m_collisions.m_collidingIdsSingle.count(myEnt->m_id);

      if (willCollide) {
        // if there is a collision, wait
        system->getEnt(c.m_entID)->get<Physics>()->m_v = glm::vec2(0.0);

        double dist = glm::max(glm::abs(system->m_collisions.m_closestDeltas[c.m_entID].x),
                               glm::abs(system->m_collisions.m_closestDeltas[c.m_entID].y));

        glm::vec2 pos = system->getEnt(c.m_entID)->getPosition();
        glm::vec2 shape = system->getEnt(c.m_entID)->get<Shape>()->m_dimensions;

        if (game->m_mouseX >= pos.x && game->m_mouseX <= pos.x + shape.x &&
            game->m_mouseY >= pos.y && game->m_mouseY <= pos.y + shape.y) {
          LOG_ERR("Min displacement: %f :: %f",
                  dist,
                  system->getEnt(c.m_entID)->get<Shape>()->m_dimensions.x);
        }

        //      if (dist <= system->getEnt(m_entID)->get<Shape>()->m_dimensions.x) {
        //        system->getEnt(m_entID)->get<Graphics>()->m_color =
        //          (SDL_Color) {0x00, 0xFF, 0xFF, 0xFF};
        //      } else {
        //        system->getEnt(m_entID)->get<Graphics>()->m_color =
        //            (SDL_Color) {0xFF, 0x00, 0x00, 0xFF};
        //      }

        myEnt->get<Physics>()->m_v = glm::vec2(0);

        // only allow to move if there is space
        c.move(game, system, c.m_goalxy.x, c.m_goalxy.y);

        glm::vec2 vel = system->getEnt(c.m_entID)->get<Physics>()->m_v;
        glm::vec2 dim = system->getEnt(c.m_entID)->get<Shape>()->m_dimensions;
        double max_posx = vel.x;
        double max_posy = vel.y;
        double min_negx = vel.x;
        double min_negy = vel.y;

        if (max_posx < 0) max_posx = 0;
        if (max_posy < 0) max_posy = 0;
        if (min_negx > 0) min_negx = 0;
        if (min_negy > 0) min_negy = 0;

        for (auto &pair : system->m_collisions.m_collidingDeltas[c.m_entID]) {
          if (game->m_mouseX >= pos.x && game->m_mouseX <= pos.x + shape.x &&
              game->m_mouseY >= pos.y && game->m_mouseY <= pos.y + shape.y) {
            LOG_ERR("%f, %f :: %f, %f", pair.second.x, pair.second.y, dim.x, dim.y);
          }

          if (glm::abs(pair.second.x) > glm::abs(pair.second.y)) {
            if (pair.second.x > 0) {
              if (pair.second.x - dim.x >= 0 &&
                  pair.second.x - dim.x <= max_posx) {
                max_posx = pair.second.x - dim.x;
              }
              if (pair.second.x - dim.x <= 0) {
                //              system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
                max_posx = 0;
              }
            }

            if (pair.second.x <= 0) {
              if (pair.second.x + dim.x <= 0 &&
                  pair.second.x + dim.x >= min_negx) {
                min_negx = pair.second.x + dim.x;
              }
              if (pair.second.x + dim.x >= 0) {
                //              system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
                min_negx = 0;
              }
            }
          } else {
            if (pair.second.y > 0) {
              if (pair.second.y - dim.y >= 0 &&
                  pair.second.y - dim.y <= max_posy) {
                max_posy = pair.second.y - dim.y;
              }
              if (pair.second.y - dim.y <= 0) {
                //              system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
                max_posy = 0;
              }
            }

            if (pair.second.y <= 0) {
              if (pair.second.y + dim.y <= 0 &&
                  pair.second.y + dim.y >= min_negy) {
                min_negy = pair.second.y + dim.y;
              }
              if (pair.second.y + dim.y >= 0) {
                //              system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
                min_negy = 0;
              }
            }
          }

          if (game->m_mouseX >= pos.x && game->m_mouseX <= pos.x + shape.x &&
              game->m_mouseY >= pos.y && game->m_mouseY <= pos.y + shape.y) {
            LOG_ERR("%f, %f : %f, %f", max_posx, max_posy, min_negx, min_negy);
          }
        }

        if (vel.x > 0) {
          vel.x = max_posx;
        }
        if (vel.x <= 0) {
          vel.x = min_negx;
        }
        if (vel.y > 0) {
          vel.y = max_posy;
        }
        if (vel.y <= 0) {
          vel.y = min_negy;
        }
        system->getEnt(c.m_entID)->get<Physics>()->m_v = vel;
      } else {
        // otherwise, keep going
        c.move(game, system, c.m_goalxy.x, c.m_goalxy.y);
      }
    }
  }
}