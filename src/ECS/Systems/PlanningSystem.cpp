/** 
 * TdECSPlanningSystem.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <TdManagers/TdCollisionQuadTree/Node.hpp>
#include <TdManagers/TdCollisionQuadTree/QuadTree.hpp>


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
    if (!(c)->m_alive) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto c = m_laserComponents.begin(); c != m_laserComponents.end();) {
    if (!(c)->m_alive) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }
  for (auto &comp : m_laserComponents) {

  }

  for (auto c = m_pathingComponents.begin(); c != m_pathingComponents.end();) {
    if (!(c)->m_alive) {
      c++;
    } else {
      (c)->update(game, system);
      c++;
    }
  }

  for (auto& c : m_pathingComponents) {

  }
}