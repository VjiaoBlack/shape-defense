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

  std::vector<std::unique_ptr<TilePosition>>
      m_tilePositionComponents;
  std::vector<std::unique_ptr<Shape>> m_shapeComponents;

  Entity* getEnt(int entID);

  void update(Game *game, bool updateGraphics = true);

  void addEntity(Game *game, std::unique_ptr<Entity> &&e);

  void addComponent(std::unique_ptr<Position> c) {
    m_physics.m_positionComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TilePosition> c) {
    m_tilePositionComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Shape> c) {
    m_shapeComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Graphics> c) {
    m_graphics.m_graphicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Health> c) {
    m_health.m_healthComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Physics> c) {
    m_physics.m_physicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<LaserShooter> c) {
    m_planning.m_laserComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Attack> c) {
    m_planning.m_attackComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<Pathing> c) {
    m_planning.m_pathingComponents.push_back(std::move(c));
  }
};
