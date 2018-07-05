#pragma once
/**
 * TdECSEntity.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_rect.h>
#include <exception>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "../Utils.hpp"
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPhysicsComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPositionComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"

#include "TdECS/TdECSSystems/TdECSSystem.hpp"

class TdECSComponent;

class TdECSMissingComponentException : public std::runtime_error {
 public:
  TdECSMissingComponentException(const std::string &__arg)
      : runtime_error(__arg) {}
};

class TdECSEntity {
 public:
  bool m_dead = false;
  int m_id;

  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::map<std::string, TdECSComponent *> m_components;
  TdECSSystem *m_GUISystem;

  TdECSEntity() = delete;
  TdECSEntity(TdECSSystem *GUISystem)
      : m_id(GUISystem->m_nextEntityId), m_GUISystem(GUISystem) {
    m_components = std::map<std::string, TdECSComponent *>();
  }

  template <class T>
  void addComponent(std::unique_ptr<T> &&component) {
    component->m_entId = m_id;
    m_components[typeid(T).name()] = component.get();
    if (m_GUISystem) {
      m_GUISystem->addComponent(std::move(component));
    }
  }

  void die() {
    for (auto cp : m_components) {
      cp.second->m_dead = true;
    }
    m_dead = true;
  }

  template <class T>
  T *get() {
    if (!m_components.count(typeid(T).name())) {
      std::string msg = "missing component: ";
      msg += typeid(T).name();
      throw TdECSMissingComponentException(msg);
    }
    return static_cast<T *>(m_components[typeid(T).name()]);
  }

  template <class T>
  bool has() {
    return m_components.count(typeid(T).name()) > 0;
  }

  static TdECSEntity *addPlayerBase(TdGame *game, TdECSSystem *system) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(48, 48);
    auto tilePosComp = std::make_unique<TdECSTilePositionComponent>(0, 0);
    auto shooterComp = std::make_unique<TdECSShooterComponent>(5, 1, 30);
    auto healthComp = std::make_unique<TdECSHealthComponent>(3000000, 2);

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(shooterComp));
    entity->addComponent(std::move(healthComp));

    auto pt = entity.get();
    system->addEntity(std::move(entity));
    return pt;
  }

  static TdECSEntity *addTower(TdGame *game, TdECSSystem *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(32, 32);
    auto tilePosComp =
        std::make_unique<TdECSTilePositionComponent>(tileX, tileY);
    auto healthComp = std::make_unique<TdECSHealthComponent>(100, 0);
    auto shooterComp = std::make_unique<TdECSShooterComponent>(5, 2, 30);

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(shooterComp));

    auto pt = entity.get();
    system->addEntity(std::move(entity));

    return pt;
  }

  static TdECSEntity *addEnemy(TdGame *game, TdECSSystem *system, double x,
                               double y) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFC06060));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(16, 16);
    auto positionComp = std::make_unique<TdECSPositionComponent>(x, y, 0);
    auto physicsComp = std::make_unique<TdECSPhysicsComponent>();
    auto healthComp = std::make_unique<TdECSHealthComponent>(10, 0);
    auto fighterComp = std::make_unique<TdECSFighterComponent>(5, 0.5, 30);

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(positionComp));
    entity->addComponent(std::move(physicsComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(fighterComp));

    auto pt = entity.get();
    system->addEntity(std::move(entity));

    return pt;
  }
};
