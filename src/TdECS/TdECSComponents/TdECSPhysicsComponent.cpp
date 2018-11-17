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
  system->getEnt(m_entID)->get<TdECSPositionComponent>()->m_p += m_v;
}
