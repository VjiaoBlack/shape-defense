/** 
 * TdECSHealthComponent.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include <TdGame.hpp>
#include "TdECSHealthComponent.hpp"
#include "../TdECSEntity.hpp"

#include "TdRenderLoop/TdGameLoop.hpp"

void TdECSHealthComponent::update(TdGame *game, TdECSSystem *system) {
  if (m_curHealth <= 0.0) {
    system->m_collisions.m_qtree->removeEntID(game, system, m_entID);
    system->getEnt(m_entID)->die();
  }
}