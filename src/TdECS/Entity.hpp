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
#include "TdECS/TdECSComponents/Attack.hpp"
#include "TdECS/TdECSComponents/Fighter.hpp"
#include "TdECS/TdECSComponents/Health.hpp"
#include "TdECS/TdECSComponents/LaserShooter.hpp"
#include "TdECS/TdECSComponents/Pathing.hpp"
#include "TdECS/TdECSComponents/Physics.hpp"
#include "TdECS/TdECSComponents/Position.hpp"
#include "TdECS/TdECSComponents/Shooter.hpp"

#include "TdECS/TdECSSystems/System.hpp"

class Component;

class MissingComponentException : public std::runtime_error {
 public:
  MissingComponentException(const std::string &__arg)
      : runtime_error(__arg) {}
};

class Entity {
 public:
  bool m_dead = false;
  int m_id;

  inline glm::dvec2 getPosition() {
    if (this->has<TilePosition>()) {
      return this->get<TilePosition>()->m_xy * 16 +
             glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2;
    } else if (this->has<Position>()) {
      return glm::dvec2(this->get<Position>()->m_p);
    } else {
      std::string msg = "missing component: general position";
      throw MissingComponentException(msg);
    }
  };

  inline glm::dvec2 getCenterPosition() {
    if (this->has<TilePosition>()) {
      return this->get<TilePosition>()->m_xy * 16 +
             glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2 +
             glm::ivec2(this->get<Shape>()->m_dimensions / 2.0);
    } else if (this->has<Position>()) {
      return this->get<Position>()->m_p +
             this->get<Shape>()->m_dimensions / 2.0;
    } else {
      std::string msg = "missing component: general position";
      throw MissingComponentException(msg);
    }
  };

  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::map<std::string, Component *> m_components;
  System *m_GUISystem;

  Entity() = delete;
  Entity(System *GUISystem)
      : m_id(GUISystem->m_nextEntityId), m_GUISystem(GUISystem) {
    m_components = std::map<std::string, Component *>();
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
//    if (!m_components.count(typeid(T).name())) {
//      std::string msg = "missing component: ";
//      msg += typeid(T).name();
//      throw MissingComponentException(msg);
//    }
    return static_cast<T *>(m_components[typeid(T).name()]);
  }

  template <class T>
  inline bool has() {
    return m_components.count(typeid(T).name()) > 0;
  }

  static Entity *addPlayerBase(Game *game, System *system) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp =
        std::make_unique<Graphics>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<Shape>(48, 48);
    auto tilePosComp = std::make_unique<TilePosition>(0, 0);
    auto shooterComp = std::make_unique<Shooter>();
    auto healthComp = std::make_unique<Health>(3000000, 2);
    auto attackComp = std::make_unique<Attack>(0, 10, 0.3);
    auto laserComp = std::make_unique<LaserShooter>();

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

  static Entity *addTower(Game *game, System *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp =
        std::make_unique<Graphics>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<Shape>(32, 32);
    auto tilePosComp =
        std::make_unique<TilePosition>(tileX, tileY);
    auto healthComp = std::make_unique<Health>(100, 0);
    auto shooterComp = std::make_unique<Shooter>();
    auto attackComp = std::make_unique<Attack>(0, 5, 1.5);
    auto laserComp = std::make_unique<LaserShooter>();

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

  static Entity *addWall(Game *game, System *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp =
        std::make_unique<Graphics>(convertColorType(0xFFFFFFFF));
    auto shapeComp = std::make_unique<Shape>(16, 16);
    auto tilePosComp =
        std::make_unique<TilePosition>(tileX, tileY);
    auto healthComp = std::make_unique<Health>(500, 2);

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(tilePosComp));
    entity->addComponent(std::move(healthComp));

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }

  static Entity *addEnemy(Game *game, System *system, double x,
                               double y) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp =
        std::make_unique<Graphics>(convertColorType(0xFFC06060));
    auto shapeComp = std::make_unique<Shape>(16, 16);
    auto positionComp = std::make_unique<Position>(x, y);
    auto physicsComp = std::make_unique<Physics>();
    auto healthComp = std::make_unique<Health>(10, 0);
    auto fighterComp = std::make_unique<Fighter>();
    auto attackComp = std::make_unique<Attack>(1, 3, 0.5);
    auto laserComp = std::make_unique<LaserShooter>();

    entity->addComponent(std::move(graphicsComp));
    entity->addComponent(std::move(shapeComp));
    entity->addComponent(std::move(positionComp));
    entity->addComponent(std::move(physicsComp));
    entity->addComponent(std::move(healthComp));
    entity->addComponent(std::move(fighterComp));
    entity->addComponent(std::move(attackComp));
    entity->addComponent(std::move(laserComp));
    entity->addComponent(std::make_unique<Pathing>());

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }
};
