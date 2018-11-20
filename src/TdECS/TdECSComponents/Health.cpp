/** 
 * TdECSHealthComponent.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <Game.hpp>
#include "Health.hpp"
#include "TdECS/Entity.hpp"

#include "TdRenderLoop/GameLoop.hpp"
#include "TdECS/TdECSSystems/TdCollisionQuadTree/QuadTree.hpp"

void Health::update(Game *game, System *system) {
  if (m_curHealth <= 0.0) {
    system->m_collisions.m_qtree->removeEntID(game, system, m_entID);
    system->getEnt(m_entID)->die();
  }
}