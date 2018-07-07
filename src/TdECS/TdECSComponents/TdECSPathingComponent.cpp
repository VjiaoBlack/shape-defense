/**
 * TdECSPathingComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "../../TdGame.hpp"
#include "../TdECSEntity.hpp"
#include "../TdECSSystems/TdECSSystemUtils.hpp"

#include "TdECSPathingComponent.hpp"
#include "TdECSPhysicsComponent.hpp"

void TdECSPathingComponent::move(TdGame* game, TdECSSystem* system, double x,
                                 double y) {
  m_goalX = x;
  m_goalY = y;
  auto myEnt = system->m_entities[m_entID].get();
  double entX, entY;
  std::tie(entX, entY) = getCenterPosition(myEnt);

  double entXDist = m_goalX - entX;
  double entYDist = m_goalY - entY;
  double dist = sqrt((entXDist * entXDist) + (entYDist * entYDist));

  myEnt->get<TdECSPhysicsComponent>()->m_vx =
      60.0 * game->m_deltaTime * entXDist / (dist * 1000.0);
  myEnt->get<TdECSPhysicsComponent>()->m_vy =
      60.0 * game->m_deltaTime * entYDist / (dist * 1000.0);
  m_isMoving = true;
}

void TdECSPathingComponent::stop(TdGame* game, TdECSSystem* system) {
  m_isMoving = false;

  system->m_entities[m_entID]->get<TdECSPhysicsComponent>()->m_vx = 0;
  system->m_entities[m_entID]->get<TdECSPhysicsComponent>()->m_vy = 0;
}

void TdECSPathingComponent::update(TdGame* game, TdECSSystem* system) {
  if (m_isMoving) {
    // find collision
    auto myEnt = system->m_entities[m_entID].get();
    bool willCollide = system->willCollide(myEnt);

    if (willCollide) {
      // if there is a collision, wait
      system->m_entities[m_entID]->get<TdECSPhysicsComponent>()->m_vx = 0;
      system->m_entities[m_entID]->get<TdECSPhysicsComponent>()->m_vy = 0;
    } else {
      // otherwise, keep going
      this->move(game, system, m_goalX, m_goalY);
    }
  }
}
