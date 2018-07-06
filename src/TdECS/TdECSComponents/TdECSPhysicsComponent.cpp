/**
 * TdECSPhysicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSPhysicsComponent.hpp"
#include "TdECSPositionComponent.hpp"
#include "../TdECSEntity.hpp"

void TdECSPhysicsComponent::update(TdGame *game, TdECSSystem *system) {
  system->m_entities[m_entID]->get<TdECSPositionComponent>()->m_x += m_vx;
  system->m_entities[m_entID]->get<TdECSPositionComponent>()->m_y += m_vy;
  system->m_entities[m_entID]->get<TdECSPositionComponent>()->m_theta += m_vtheta;
}
