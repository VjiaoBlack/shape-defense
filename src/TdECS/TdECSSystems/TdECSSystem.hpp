#pragma once
/**
 * TdECSSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#pragma once

/**
 * TdGUISystem.hpp
 *
 * Victor Jiao
 *
 * Handles a GUI System.
 */

#include <map>
#include <memory>
#include "TdECS/TdECSComponents/TdECSLaserShooterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSAttackComponent.hpp"

#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPhysicsComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPositionComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSTilePositionComponent.hpp"

#include "TdECSGraphicsSystem.hpp"
#include "TdECSHealthSystem.hpp"
#include "TdECSPhysicsSystem.hpp"
#include "TdECSPlanningSystem.hpp"

class TdECSEntity;
class TdGame;

class TdECSSystem {
 public:
  int m_nextEntityId = 0;

  TdECSGraphicsSystem m_graphics;
  TdECSPhysicsSystem m_physics;
  TdECSPlanningSystem m_planning;
  TdECSHealthSystem m_health;

  std::map<int, std::unique_ptr<TdECSEntity>> m_entities;

  std::vector<std::unique_ptr<TdECSTilePositionComponent>>
      m_tilePositionComponents;
  std::vector<std::unique_ptr<TdECSShapeComponent>> m_shapeComponents;

  void update(TdGame *game, bool updateGraphics = true);

  // currently uses rectangle collisions
  bool isColliding(TdECSEntity* ent1, TdECSEntity* ent2);
  bool willCollide(TdECSEntity* ent1, TdECSEntity* ent2);
  bool bubbleWillCollide(TdECSEntity* ent1, TdECSEntity* ent2);

  bool isColliding(TdECSEntity* ent);
  bool willCollide(TdECSEntity* ent);
  bool bubbleWillCollide(TdECSEntity* ent);

  void addEntity(std::unique_ptr<TdECSEntity> &&e);

  void addComponent(std::unique_ptr<TdECSPositionComponent> c) {
    m_physics.m_positionComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSTilePositionComponent> c) {
    m_tilePositionComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSShapeComponent> c) {
    m_shapeComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSGraphicsComponent> c) {
    m_graphics.m_graphicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSFighterComponent> c) {
    m_planning.m_fighterComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSShooterComponent> c) {
    m_planning.m_shooterComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSHealthComponent> c) {
    m_health.m_healthComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSPhysicsComponent> c) {
    m_physics.m_physicsComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSLaserShooterComponent> c) {
    m_planning.m_laserComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSAttackComponent> c) {
    m_planning.m_attackComponents.push_back(std::move(c));
  }

  void addComponent(std::unique_ptr<TdECSPathingComponent> c) {
    m_planning.m_pathingComponents.push_back(std::move(c));
  }
};
