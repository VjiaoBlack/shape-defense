/**
 * Physics.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Physics.hpp"

#include <Game.hpp>

#include <ECS/Systems/System.hpp>

void Physics::update(Game *game, System *system) {
  system->getEnt(m_entID)->get<Position>()->m_p += m_v;
}