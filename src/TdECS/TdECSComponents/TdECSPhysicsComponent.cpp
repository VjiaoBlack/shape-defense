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

void TdECSPhysicsComponent::update(TdGame* game) {
  m_ent->get<TdECSPositionComponent>()->m_x += m_vx;
  m_ent->get<TdECSPositionComponent>()->m_y += m_vy;
  m_ent->get<TdECSPositionComponent>()->m_theta += m_vtheta;
}
