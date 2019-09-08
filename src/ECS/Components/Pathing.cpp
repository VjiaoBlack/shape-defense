/**
 * Pathing.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "LaserShooter.hpp"

#include <Game.hpp>

#include <ECS/Systems/System.hpp>

void Pathing::update(Game *game, System *system) {
  if (!m_alive) {
    return;
  }
  if (m_isMoving) {
    // find collision
    auto myEnt = system->getEnt(m_entID);

    bool willCollide = system->m_collisions.m_collidingIdsSingle.count(myEnt->m_id);

    if (willCollide) {
      // if there is a collision, wait
      system->getEnt(m_entID)->get<Physics>()->m_v = glm::vec2(0.0);

      double dist = glm::max(glm::abs(system->m_collisions.m_closestDeltas[m_entID].x),
                             glm::abs(system->m_collisions.m_closestDeltas[m_entID].y));

      glm::vec2 pos   = system->getEnt(m_entID)->getPosition();
      glm::vec2 shape = system->getEnt(m_entID)->get<Shape>()->m_dimensions;

      if (game->m_mouseX >= pos.x && game->m_mouseX <= pos.x + shape.x &&
          game->m_mouseY >= pos.y && game->m_mouseY <= pos.y + shape.y) {
        LOG_ERR("Min displacement: %f :: %f",
                dist,
                system->getEnt(m_entID)->get<Shape>()->m_dimensions.x);
      }

      myEnt->get<Physics>()->m_v = glm::vec2(0);

      // only allow to move if there is space
      this->move(game, system, m_goalxy.x, m_goalxy.y);

      glm::vec2 vel      = system->getEnt(m_entID)->get<Physics>()->m_v;
      glm::vec2 dim      = system->getEnt(m_entID)->get<Shape>()->m_dimensions;
      double    max_posx = vel.x;
      double    max_posy = vel.y;
      double    min_negx = vel.x;
      double    min_negy = vel.y;

      if (max_posx < 0) max_posx                   = 0;
      if (max_posy < 0) max_posy                   = 0;
      if (min_negx > 0) min_negx                   = 0;
      if (min_negy > 0) min_negy                   = 0;

      for (auto &pair : system->m_collisions.m_collidingDeltas[m_entID]) {
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
              // system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
              max_posx = 0;
            }
          }

          if (pair.second.x <= 0) {
            if (pair.second.x + dim.x <= 0 &&
                pair.second.x + dim.x >= min_negx) {
              min_negx = pair.second.x + dim.x;
            }
            if (pair.second.x + dim.x >= 0) {
              // system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
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
              // system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
              max_posy = 0;
            }
          }

          if (pair.second.y <= 0) {
            if (pair.second.y + dim.y <= 0 &&
                pair.second.y + dim.y >= min_negy) {
              min_negy = pair.second.y + dim.y;
            }
            if (pair.second.y + dim.y >= 0) {
              // system->getEnt(m_entID)->get<Graphics>()->m_color = {0x00, 0xFF, 0x00, 0xFF};
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
      system->getEnt(m_entID)->get<Physics>()->m_v = vel;
    } else {
      // otherwise, keep going
      this->move(game, system, m_goalxy.x, m_goalxy.y);
    }
  }
}