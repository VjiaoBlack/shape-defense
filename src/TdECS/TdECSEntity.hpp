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
#include "TdECS/TdECSComponents/TdECSAttackComponent.hpp"
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSLaserShooterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPathingComponent.hpp"
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

  inline glm::dvec2 getPosition() {
    if (this->has<TdECSTilePositionComponent>()) {
      return glm::dvec2(
          this->get<TdECSTilePositionComponent>()->m_x * 16 + K_DISPLAY_SIZE_X / 2,
          this->get<TdECSTilePositionComponent>()->m_y * 16 +
              K_DISPLAY_SIZE_Y / 2);
    } else if (this->has<TdECSPositionComponent>()) {
      return glm::dvec2(this->get<TdECSPositionComponent>()->m_x,
                        this->get<TdECSPositionComponent>()->m_y);
    } else {
      std::string msg = "missing component: general position";
      throw TdECSMissingComponentException(msg);
    }
  };

  inline glm::dvec2 getCenterPosition() {
    if (this->has<TdECSTilePositionComponent>()) {
      return glm::dvec2(this->get<TdECSTilePositionComponent>()->m_x * 16 +
                            K_DISPLAY_SIZE_X / 2 +
                            this->get<TdECSShapeComponent>()->m_width / 2.0,
                        this->get<TdECSTilePositionComponent>()->m_y * 16 +
                            K_DISPLAY_SIZE_Y / 2 +
                            this->get<TdECSShapeComponent>()->m_height / 2.0);
    } else if (this->has<TdECSPositionComponent>()) {
      return glm::dvec2(this->get<TdECSPositionComponent>()->m_x +
                            this->get<TdECSShapeComponent>()->m_width / 2.0,
                        this->get<TdECSPositionComponent>()->m_y +
                            this->get<TdECSShapeComponent>()->m_height / 2.0);
    } else {
      std::string msg = "missing component: general position";
      throw TdECSMissingComponentException(msg);
    }
  };

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
    component->m_entID = m_id;
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
  inline T *get() {
    if (!m_components.count(typeid(T).name())) {
      std::string msg = "missing component: ";
      msg += typeid(T).name();
      throw TdECSMissingComponentException(msg);
    }
    return static_cast<T *>(m_components[typeid(T).name()]);
  }

  template <class T>
  inline bool has() {
    return m_components.count(typeid(T).name()) > 0;
  }

  static TdECSEntity *addPlayerBase(TdGame *game, TdECSSystem *system) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(48, 48);
    auto tilePosComp = std::make_unique<TdECSTilePositionComponent>(0, 0);
    auto shooterComp = std::make_unique<TdECSShooterComponent>();
    auto healthComp = std::make_unique<TdECSHealthComponent>(3000000, 2);
    auto attackComp = std::make_unique<TdECSAttackComponent>(0, 10, 0.3);
    auto laserComp = std::make_unique<TdECSLaserShooterComponent>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(shooterComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(attackComp));
    entity->addComponent(std::move(laserComp));

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));
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
    auto shooterComp = std::make_unique<TdECSShooterComponent>();
    auto attackComp = std::make_unique<TdECSAttackComponent>(0, 5, 1.5);
    auto laserComp = std::make_unique<TdECSLaserShooterComponent>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(shooterComp));
    entity->addComponent(std::move(attackComp));
    entity->addComponent(std::move(laserComp));

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }

  static TdECSEntity *addWall(TdGame *game, TdECSSystem *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(16, 16);
    auto tilePosComp =
        std::make_unique<TdECSTilePositionComponent>(tileX, tileY);
    auto healthComp = std::make_unique<TdECSHealthComponent>(500, 2);

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(healthComp));

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }

  static TdECSEntity *addEnemy(TdGame *game, TdECSSystem *system, double x,
                               double y) {
    auto entity = std::make_unique<TdECSEntity>(system);

    auto graphicsComp =
        std::make_unique<TdECSGraphicsComponent>(convertColorType(0xFFC06060));
    auto shapeComp = std::make_unique<TdECSShapeComponent>(8, 8);
    auto positionComp = std::make_unique<TdECSPositionComponent>(x, y);
    auto physicsComp = std::make_unique<TdECSPhysicsComponent>();
    auto healthComp = std::make_unique<TdECSHealthComponent>(10, 0);
    auto fighterComp = std::make_unique<TdECSFighterComponent>();
    auto attackComp = std::make_unique<TdECSAttackComponent>(1, 3, 0.5);
    auto laserComp = std::make_unique<TdECSLaserShooterComponent>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(positionComp));
    entity->addComponent(std::move(physicsComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(fighterComp));
    entity->addComponent(std::move(attackComp));
    entity->addComponent(std::move(laserComp));
    entity->addComponent(std::make_unique<TdECSPathingComponent>());

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }
};
