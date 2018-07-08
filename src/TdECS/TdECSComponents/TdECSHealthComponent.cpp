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
    double x, y;
    std::tie(x, y) = getCenterPosition(system->m_entities[m_entID].get());
//    printf("DEAD at %d, %d\n",(int) x, (int)y);
    system->m_collisions.m_qtree->removeEntID(game, system, m_entID);
    system->m_entities[m_entID]->die();
  }
}