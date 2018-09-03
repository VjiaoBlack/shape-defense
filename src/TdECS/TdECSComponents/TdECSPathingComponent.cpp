/**
 * TdECSPathingComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <TdECS/TdECSSystems/TdECSSystemPosUtils.hpp>
#include "../../TdGame.hpp"
#include "../TdECSEntity.hpp"
#include "../TdECSSystems/TdECSSystemUtils.hpp"

#include "TdECSPathingComponent.hpp"
#include "TdECSPhysicsComponent.hpp"

void TdECSPathingComponent::move(TdGame* game, TdECSSystem* system, double x,
                                 double y) {
  m_goalX = x;
  m_goalY = y;
  auto myEnt = system->getEnt(m_entID);
  glm::dvec2 entp = myEnt->getCenterPosition();

  double entXDist = m_goalX - entp.x;
  double entYDist = m_goalY - entp.y;
  double dist = sqrt((entXDist * entXDist) + (entYDist * entYDist));

  myEnt->get<TdECSPhysicsComponent>()->m_vx =
      60.0 * game->m_deltaTime * entXDist / (dist * 1000.0);
  myEnt->get<TdECSPhysicsComponent>()->m_vy =
      60.0 * game->m_deltaTime * entYDist / (dist * 1000.0);
  m_isMoving = true;
}

void TdECSPathingComponent::stop(TdGame* game, TdECSSystem* system) {
  m_isMoving = false;

  system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_vx = 0;
  system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_vy = 0;
}

void TdECSPathingComponent::update(TdGame* game, TdECSSystem* system) {
  if (m_isMoving) {
    // find collision
    auto myEnt = system->getEnt(m_entID);

    bool isColliding = system->m_collisions.isColliding(system, myEnt);

    if (isColliding) {
      // if there is a collision, wait
      system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_vx = 0;
      system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_vy = 0;
    } else {
      // otherwise, keep going
      this->move(game, system, m_goalX, m_goalY);
    }
  }
}
