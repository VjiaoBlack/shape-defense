/**
 * TdECSSystem.cpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "TdECSSystem.hpp"
#include "../TdECSEntity.hpp"

bool TdECSSystem::isColliding(TdECSEntity* ent1, TdECSEntity* ent2) {
  if (!ent1 || !ent2) {
    std::cerr << "Collision system passed a Null ent." << std::endl;
    return true;
  }
  double ent1x1, ent1y1, ent2x1, ent2y1;

  std::tie(ent1x1, ent1y1) = getPosition(ent1);
  double ent1x2 = ent1x1 + ent1->get<TdECSShapeComponent>()->m_width;
  double ent1y2 = ent1y1 + ent1->get<TdECSShapeComponent>()->m_height;

  std::tie(ent2x1, ent2y1) = getPosition(ent2);
  double ent2x2 = ent2x1 + ent2->get<TdECSShapeComponent>()->m_width;
  double ent2y2 = ent2y1 + ent2->get<TdECSShapeComponent>()->m_height;

  return ent1x1 < ent2x2 && ent1x2 > ent2x1 && ent1y1 < ent2y2 &&
         ent1y2 > ent2y1;
}

// note: only tests movement of ent1
// also exaggerates ent1 movements
bool TdECSSystem::willCollide(TdECSEntity* ent1, TdECSEntity* ent2) {
  if (!ent1 || !ent2) {
    std::cerr << "Collision system passed a Null ent." << std::endl;
    return true;
  }
  double ent1x1, ent1y1, ent2x1, ent2y1;
  double ent1vx = 0;
  double ent1vy = 0;
  double ent2vx = 0;
  double ent2vy = 0;

  if (ent1->has<TdECSPhysicsComponent>()) {
    ent1vx = ent1->get<TdECSPhysicsComponent>()->m_vx;
    ent1vy = ent1->get<TdECSPhysicsComponent>()->m_vy;
  }

  //  if (ent2->has<TdECSPhysicsComponent>()) {
  //    ent2vx = ent2->get<TdECSPhysicsComponent>()->m_vx;
  //    ent2vy = ent2->get<TdECSPhysicsComponent>()->m_vy;
  //  }

  std::tie(ent1x1, ent1y1) = getPosition(ent1);
  ent1x1 += ent1vx - 3.0;
  ent1y1 += ent1vy - 3.0;
  double ent1x2 = 3.0 + ent1x1 + ent1->get<TdECSShapeComponent>()->m_width;
  double ent1y2 = 3.0 + ent1y1 + ent1->get<TdECSShapeComponent>()->m_height;

  std::tie(ent2x1, ent2y1) = getPosition(ent2);
  ent2x1 += ent2vx - 3.0;
  ent2y1 += ent2vy - 3.0;
  double ent2x2 = 3.0 + ent2x1 + ent2->get<TdECSShapeComponent>()->m_width;
  double ent2y2 = 3.0 + ent2y1 + ent2->get<TdECSShapeComponent>()->m_height;

  return ent1x1 < ent2x2 && ent1x2 > ent2x1 && ent1y1 < ent2y2 &&
         ent1y2 > ent2y1;
}

// note: only tests movement of ent1
// also exaggerates ent1 movements
bool TdECSSystem::bubbleWillCollide(TdECSEntity* ent1, TdECSEntity* ent2) {
  if (!ent1 || !ent2) {
    std::cerr << "Collision system passed a Null ent." << std::endl;
    return true;
  }
  double ent1x1, ent1y1, ent2x1, ent2y1;
  double ent1vx = 0;
  double ent1vy = 0;
  double ent2vx = 0;
  double ent2vy = 0;

  if (ent1->has<TdECSPhysicsComponent>()) {
    ent1vx = ent1->get<TdECSPhysicsComponent>()->m_vx;
    ent1vy = ent1->get<TdECSPhysicsComponent>()->m_vy;
  }

  //  if (ent2->has<TdECSPhysicsComponent>()) {
  //    ent2vx = ent2->get<TdECSPhysicsComponent>()->m_vx;
  //    ent2vy = ent2->get<TdECSPhysicsComponent>()->m_vy;
  //  }

  std::tie(ent1x1, ent1y1) = getPosition(ent1);
  ent1x1 += ent1vx - 10.0;
  ent1y1 += ent1vy - 10.0;
  double ent1x2 = 10.0 + ent1x1 + ent1->get<TdECSShapeComponent>()->m_width;
  double ent1y2 = 10.0 + ent1y1 + ent1->get<TdECSShapeComponent>()->m_height;

  std::tie(ent2x1, ent2y1) = getPosition(ent2);
  ent2x1 += ent2vx - 10.0;
  ent2y1 += ent2vy - 10.0;
  double ent2x2 = 10.0 + ent2x1 + ent2->get<TdECSShapeComponent>()->m_width;
  double ent2y2 = 10.0 + ent2y1 + ent2->get<TdECSShapeComponent>()->m_height;

  return ent1x1 < ent2x2 && ent1x2 > ent2x1 && ent1y1 < ent2y2 &&
         ent1y2 > ent2y1;
}

bool TdECSSystem::isColliding(TdECSEntity* ent) {
  for (auto& itEnt : m_entities) {
    if (ent->m_id != itEnt.first &&
        this->isColliding(ent, itEnt.second.get())) {
      return true;
    }
  }
  return false;
}

bool TdECSSystem::willCollide(TdECSEntity* ent) {
  for (auto& itEnt : m_entities) {
    if (ent->m_id != itEnt.first &&
        this->willCollide(ent, itEnt.second.get())) {
      return true;
    }
  }
  return false;
}

bool TdECSSystem::bubbleWillCollide(TdECSEntity* ent) {
  for (auto& itEnt : m_entities) {
    if (ent->m_id != itEnt.first &&
        this->bubbleWillCollide(ent, itEnt.second.get())) {
      return true;
    }
  }
  return false;
}

void TdECSSystem::addEntity(std::unique_ptr<TdECSEntity>&& e) {
  m_entities[m_nextEntityId++] = std::move(e);
}

void TdECSSystem::update(TdGame* game, bool updateGraphics) {
  m_health.update(game, this);
  m_planning.update(game, this);
  m_physics.update(game, this);

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
}