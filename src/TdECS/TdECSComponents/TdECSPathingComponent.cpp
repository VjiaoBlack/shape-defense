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

    bool willCollide = system->m_collisions.m_collidingIdsSingle.count(myEnt->m_id);

    if (willCollide) {
      // if there is a collision, wait
      system->getEnt(m_entID)->get<TdECSPhysicsComponent>()->m_v = glm::vec2(0.0);

      double dist = glm::max(glm::abs(system->m_collisions.m_closestDeltas[m_entID].x),
                             glm::abs(system->m_collisions.m_closestDeltas[m_entID].y));

      glm::vec2 pos   = system->getEnt(m_entID)->getPosition();
      glm::vec2 shape = system->getEnt(m_entID)->get<TdECSShapeComponent>()->m_dimensions;

      if (game->m_mouseX >= pos.x && game->m_mouseX <= pos.x + shape.x &&
          game->m_mouseY >= pos.y && game->m_mouseY <= pos.y + shape.y) {
        LOG_ERR("Min displacement: %f :: %f",
                dist,
                system->getEnt(m_entID)->get<TdECSShapeComponent>()->m_dimensions.x);
      }

      if (dist <= system->getEnt(m_entID)->get<TdECSShapeComponent>()->m_dimensions.x) {
        system->getEnt(m_entID)->get<TdECSGraphicsComponent>()->m_color =
          (SDL_Color) {0x00, 0xFF, 0xFF, 0xFF};
      }

      myEnt->get<TdECSPhysicsComponent>()->m_v = glm::vec2(0);
    } else {
      // otherwise, keep going
      this->move(game, system, m_goalxy.x, m_goalxy.y);
    }
  }
}
