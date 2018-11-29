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

class Entity;
class Game;

class System {
 private:

 public:
  // makes sure no ents have id of 0; which would signal a corrupted ent.
  int m_nextEntityId = 1;

  GraphicsSystem  m_graphics;
  PhysicsSystem   m_physics;
  PlanningSystem  m_planning;
  HealthSystem    m_health;
  CollisionSystem m_collisions;

  std::unordered_map<int, std::unique_ptr<Entity>> m_enemies;
  std::unordered_map<int, std::unique_ptr<Entity>> m_allies;

  std::list<std::unordered_map<int, std::unique_ptr<Entity>>*> getEntityMaps() {
    std::list<std::unordered_map<int, std::unique_ptr<Entity>>*> itList;
    itList.push_back(&m_enemies);
    itList.push_back(&m_allies);

    return itList;
  };

  std::array<TilePosition, 1000> m_tilePositionComponents;
  std::array<Shape, 1000> m_shapeComponents;

  Entity* getEnt(int entID);

  void update(Game *game, bool updateGraphics = true);

  void addEntity(Game *game, std::unique_ptr<Entity> &&e);

  Position* addComponent(Position c) {
    m_physics.m_positionComponents[c.m_entID] = c;
    return &m_physics.m_positionComponents[c.m_entID];
  }

  TilePosition* addComponent(TilePosition c) {
    m_tilePositionComponents[c.m_entID] = c;
    return &m_tilePositionComponents[c.m_entID];
  }

  Shape* addComponent(Shape c) {
    m_shapeComponents[c.m_entID] = c;
    return &m_shapeComponents[c.m_entID];
  }

  Graphics* addComponent(Graphics c) {
    m_graphics.m_graphicsComponents[c.m_entID] = c;
    return &m_graphics.m_graphicsComponents[c.m_entID];
  }

  Health* addComponent(Health c) {
    m_health.m_healthComponents[c.m_entID] = c;
    return &m_health.m_healthComponents[c.m_entID];
  }

  Physics* addComponent(Physics c) {
    m_physics.m_physicsComponents[c.m_entID] = c;
    return &m_physics.m_physicsComponents[c.m_entID];
  }

  LaserShooter* addComponent(LaserShooter c) {
    m_planning.m_laserComponents[c.m_entID] = c;
    return &m_planning.m_laserComponents[c.m_entID];
  }

  Attack* addComponent(Attack c) {
    m_planning.m_attackComponents[c.m_entID] = c;
    return &m_planning.m_attackComponents[c.m_entID];
  }

  Pathing* addComponent(Pathing c) {
    m_planning.m_pathingComponents[c.m_entID] = c;
    return &m_planning.m_pathingComponents[c.m_entID];
  }
};
