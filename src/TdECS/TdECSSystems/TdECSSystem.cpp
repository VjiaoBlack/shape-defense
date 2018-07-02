/**
 * TdECSSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSSystem.hpp"
#include "../TdECSEntity.hpp"

void TdECSSystem::addEntity(std::unique_ptr<TdECSEntity>&& e) {
  m_entities[m_nextEntityId++] = std::move(e);
}

void TdECSSystem::update(TdGame* game, bool updateGraphics) {
  m_health.update(game, this);
  m_physics.update(game, this);
  m_planning.update(game, this);

  if (updateGraphics) {
    m_graphics.update(game, this);
  }

  for (auto c = m_entities.begin(); c != m_entities.end();) {
    if ((*c).second->m_dead) {
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