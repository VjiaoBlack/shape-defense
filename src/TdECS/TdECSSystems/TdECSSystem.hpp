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

#include <memory>
#include "TdECS/TdECSComponents/TdECSTilePositionComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPositionComponent.hpp"
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPhysicsComponent.hpp"

#include "TdECSGraphicsSystem.hpp"
#include "TdECSPhysicsSystem.hpp"
#include "TdECSPlanningSystem.hpp"
#include "TdECSHealthSystem.hpp"

class TdECSEntity;
class TdGame;

class TdECSSystem {
 public:
  TdECSGraphicsSystem m_graphics;
  TdECSPhysicsSystem m_physics;
  TdECSPlanningSystem m_planning;
  TdECSHealthSystem m_health;

  std::vector<std::unique_ptr<TdECSEntity>> m_entities;

  std::vector<std::unique_ptr<TdECSTilePositionComponent>> m_tilePositionComponents;
  std::vector<std::unique_ptr<TdECSShapeComponent>> m_shapeComponents;

  void update(TdGame *game);

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
};
