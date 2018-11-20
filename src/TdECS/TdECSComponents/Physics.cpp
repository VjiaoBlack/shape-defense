/**
 * TdECSPhysicsComponent.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Physics.hpp"
#include "Position.hpp"
#include "TdECS/Entity.hpp"

void Physics::update(Game *game, System *system) {
  system->getEnt(m_entID)->get<Position>()->m_p += m_v;
}
