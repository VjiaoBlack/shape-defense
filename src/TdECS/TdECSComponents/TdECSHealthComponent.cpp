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
    system->m_entities[m_entID]->die();
  }
}