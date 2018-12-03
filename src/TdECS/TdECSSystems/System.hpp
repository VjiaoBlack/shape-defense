#pragma once
/**
 * TdECSSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <map>
#include <unordered_map>
#include <memory>
#include <list>
#include <array>

#include "TdECS/TdECSComponents/LaserShooter.hpp"
#include "TdECS/TdECSComponents/Attack.hpp"

#include "TdECS/TdECSComponents/Health.hpp"
#include "TdECS/TdECSComponents/Physics.hpp"
#include "TdECS/TdECSComponents/Position.hpp"
#include "TdECS/TdECSComponents/TilePosition.hpp"

#include "GraphicsSystem.hpp"
#include "HealthSystem.hpp"
#include "PhysicsSystem.hpp"
#include "PlanningSystem.hpp"
#include "CollisionSystem.hpp"

#include "TdECS/Entity.hpp"

#include "SystemUtils.hpp"

class Game;

extern const uint16_t k_MAX_ENTS;
class System {
 private:

 public:
  // makes sure no ents have id of 0; which would signal a corrupted ent.
  std::array<uint16_t, k_MAX_ENTS> m_openSlots;
  uint16_t m_head = 0;
  uint16_t m_tail = k_MAX_ENTS - 1;

  GraphicsSystem  m_graphics;
  PhysicsSystem   m_physics;
  PlanningSystem  m_planning;
  HealthSystem    m_health;
  CollisionSystem m_collisions;

  std::array<Entity, k_MAX_ENTS> m_enemies;
  std::array<Entity, k_MAX_ENTS> m_allies;

  std::list<std::array<Entity, k_MAX_ENTS>*> getEntityMaps() {
    std::list<std::array<Entity, k_MAX_ENTS>*> itList;
    itList.push_back(&m_enemies);
    itList.push_back(&m_allies);

    return itList;
  };

  std::array<TilePosition, k_MAX_ENTS> m_tilePositionComponents;
  std::array<Shape, k_MAX_ENTS> m_shapeComponents;

  System() {
    for (uint16_t i = 0; i < k_MAX_ENTS; i++) {
      m_openSlots[i] = i+1;
    }
  }

  Entity* getEnt(int entID);

  void update(Game *game, bool updateGraphics = true);

  void addEntity(Game *game, Entity e);

  Position* addComponent(Position c) {
    m_physics.m_positionComponents[c.m_entID-1] = c;
    return &m_physics.m_positionComponents[c.m_entID-1];
  }

  TilePosition* addComponent(TilePosition c) {
    m_tilePositionComponents[c.m_entID-1] = c;
    return &m_tilePositionComponents[c.m_entID-1];
  }

  Shape* addComponent(Shape c) {
    m_shapeComponents[c.m_entID-1] = c;
    return &m_shapeComponents[c.m_entID-1];
  }

  Graphics* addComponent(Graphics c) {
    m_graphics.m_graphicsComponents[c.m_entID-1] = c;
    return &m_graphics.m_graphicsComponents[c.m_entID-1];
  }

  Health* addComponent(Health c) {
    m_health.m_healthComponents[c.m_entID-1] = c;
    return &m_health.m_healthComponents[c.m_entID-1];
  }

  Physics* addComponent(Physics c) {
    m_physics.m_physicsComponents[c.m_entID-1] = c;
    return &m_physics.m_physicsComponents[c.m_entID-1];
  }

  LaserShooter* addComponent(LaserShooter c) {
    m_planning.m_laserComponents[c.m_entID-1] = c;
    return &m_planning.m_laserComponents[c.m_entID-1];
  }

  Attack* addComponent(Attack c) {
    m_planning.m_attackComponents[c.m_entID-1] = c;
    return &m_planning.m_attackComponents[c.m_entID-1];
  }

  Pathing* addComponent(Pathing c) {
    m_planning.m_pathingComponents[c.m_entID-1] = c;
    return &m_planning.m_pathingComponents[c.m_entID-1];
  }
};
