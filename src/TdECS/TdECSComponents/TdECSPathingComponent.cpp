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
  m_goalxy = glm::dvec2(x, y);
  auto myEnt = system->getEnt(m_entID);
  glm::dvec2 entxy = myEnt->getCenterPosition();

  glm::dvec2 entdistxy = m_goalxy - entxy;
  double dist = sqrt(glm::dot(entdistxy, entdistxy));

  myEnt->get<TdECSPhysicsComponent>()->m_v =
      60.0 * game->m_deltaTime * entdistxy / (dist * 1000.0);
  m_isMoving = true;
}

void TdECSPathingComponent::stop(TdGame* game, TdECSSystem* system) {
  m_isMoving = false;

  system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_v = glm::vec2(0.0);
}

void TdECSPathingComponent::update(TdGame* game, TdECSSystem* system) {
  if (m_isMoving) {
    // find collision
    auto myEnt = system->getEnt(m_entID);

//    bool willCollide = system->m_collisions.willCollide(system, myEnt);
    bool willCollide = system->m_collisions.m_collidingIdsSingle.count(myEnt->m_id);

    if (willCollide) {
      // if there is a collision, wait
      system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_v = glm::vec2(0.0);
    } else {
      // otherwise, keep going
      this->move(game, system, m_goalxy.x, m_goalxy.y);
    }
  }
}
