/** 
 * TdECSHealthComponent.cpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSHealthComponent.hpp"
#include "../TdECSEntity.hpp"

void TdECSHealthComponent::update(TdGame* game) {
  if (m_health <= 0.0) {
    m_ent->die();
  }
}