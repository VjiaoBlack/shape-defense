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

  std::array<TilePosition, k_MAX_ENTS> m_tilePositionComponents;
  std::array<Shape,        k_MAX_ENTS> m_shapeComponents;

  std::array<Entity, k_MAX_ENTS> m_enemies;
  std::array<Entity, k_MAX_ENTS> m_allies;

  System() {
    for (uint16_t i = 0; i < k_MAX_ENTS; i++) {
      m_openSlots[i] = i+1;
    }
  }

  std::list<std::array<Entity, k_MAX_ENTS>*> getEntityMaps() {
    std::list<std::array<Entity, k_MAX_ENTS>*> itList;
    itList.push_back(&m_enemies);
    itList.push_back(&m_allies);

    return itList;
  };

  void update(Game *game, bool updateGraphics = true);

  Entity* getEnt(int entID);
  void addEntity(Game *game, Entity e);

  template <typename T>
  std::array<T,            k_MAX_ENTS>& getCompArray();
  template<>
  std::array<Position,     k_MAX_ENTS>& getCompArray() { return m_physics.m_positionComponents; };
  template<>
  std::array<TilePosition, k_MAX_ENTS>& getCompArray() { return m_tilePositionComponents; };
  template<>
  std::array<Shape,        k_MAX_ENTS>& getCompArray() { return m_shapeComponents; };
  template<>
  std::array<Graphics,     k_MAX_ENTS>& getCompArray() { return m_graphics.m_graphicsComponents; };
  template<>
  std::array<Health,       k_MAX_ENTS>& getCompArray() { return m_health.m_healthComponents; };
  template<>
  std::array<Physics,      k_MAX_ENTS>& getCompArray() { return m_physics.m_physicsComponents; };
  template<>
  std::array<LaserShooter, k_MAX_ENTS>& getCompArray() { return m_planning.m_laserComponents; };
  template<>
  std::array<Attack,       k_MAX_ENTS>& getCompArray() { return m_planning.m_attackComponents; };
  template<>
  std::array<Pathing,      k_MAX_ENTS>& getCompArray() { return m_planning.m_pathingComponents; };

  template <typename T>
  T* addComponent(T c) {
    this->getCompArray<T>()[c.m_entID-1] = c;
    return &this->getCompArray<T>()[c.m_entID-1];
  }
};
