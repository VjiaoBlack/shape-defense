/**
 * TdECSSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSSystem.hpp"
#include "../TdECSEntity.hpp"

void TdECSSystem::update(TdGame *game) {
  m_health.update(game);
  m_physics.update(game);
  m_planning.update(game);
  m_graphics.update(game);

  for (auto c = m_entities.begin(); c != m_entities.end();) {
    if ((*c)->m_dead) {
      c = m_entities.erase(c);
    } else {
      c++;
    }
  }
//
//  printf("%d\n", m_entities.size());
//  for (auto &h : m_health.m_healthComponents) {
//    printf("%f\n", h->m_health);
//  }
//  printf("\n");

}