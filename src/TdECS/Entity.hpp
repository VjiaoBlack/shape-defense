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
#include "TdECS/TdECSComponents/Health.hpp"
#include "TdECS/TdECSComponents/LaserShooter.hpp"
#include "TdECS/TdECSComponents/Pathing.hpp"
#include "TdECS/TdECSComponents/Physics.hpp"
#include "TdECS/TdECSComponents/Position.hpp"

#include "TdECS/TdECSSystems/System.hpp"

class Component;

template<typename T>
struct classToInt {};

template<> struct classToInt<Attack>       { enum { value = 1 };  };
template<> struct classToInt<Health>       { enum { value = 3 };  };
template<> struct classToInt<LaserShooter> { enum { value = 4 };  };
template<> struct classToInt<Pathing>      { enum { value = 5 };  };
template<> struct classToInt<Physics>      { enum { value = 6 };  };
template<> struct classToInt<TilePosition> { enum { value = 7 };  };
template<> struct classToInt<Position>     { enum { value = 8 };  };
template<> struct classToInt<Shape>        { enum { value = 10 }; };
template<> struct classToInt<Graphics>     { enum { value = 11 }; };

class MissingComponentException : public std::runtime_error {
 public:
  MissingComponentException(const std::string &__arg)
      : runtime_error(__arg) {}
};

class Entity {
 public:
  bool m_alive = true;
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
  std::map<int, Component *> m_components;
  System *m_system;

  Entity() = delete;
  Entity(System *GUISystem)
      : m_id(GUISystem->m_nextEntityId), m_system(GUISystem) {
    m_components = std::map<int, Component *>();
  }

  template <class T>
  void addComponent(T component) {
    component.m_entID = m_id;

    if (m_system) {
      m_components[classToInt<T>::value] = m_system->addComponent(component);
    } else {
      printf("NO SYSTEM\n");
      exit(1);
    }
  }

  void die() {
    for (auto cp : m_components) {
      cp.second->m_alive = false;
    }
    m_alive = false;
  }

  template <class T>
  inline T *get() {
    return static_cast<T *>(m_components[classToInt<T>::value]);
  }

  template <class T>
  inline bool has() {
    return m_components.count(classToInt<T>::value) > 0;
  }

  static Entity *addPlayerBase(Game *game, System *system) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
    auto shapeComp = Shape(48, 48);
    auto tilePosComp = TilePosition(0, 0);
    auto healthComp = Health(3000000, 2);
    auto attackComp = Attack(0, 10, 0.3, Attack::SHOOTER);
    auto laserComp = LaserShooter();

    // TODO: currently make a new copy of components for temp
    // but we want to remove this later.
    entity->addComponent(graphicsComp);
    entity->addComponent(shapeComp);
    entity->addComponent(tilePosComp);
    entity->addComponent(healthComp);
    entity->addComponent(attackComp);
    entity->addComponent(laserComp);

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));
    return pt;
  }

  static Entity *addTower(Game *game, System *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
    auto shapeComp = Shape(32, 32);
    auto tilePosComp = TilePosition(tileX, tileY);
    auto healthComp = Health(100, 0);
    auto attackComp = Attack(0, 5, 1.5, Attack::SHOOTER);
    auto laserComp = LaserShooter();

    entity->addComponent(graphicsComp);
    entity->addComponent(shapeComp);
    entity->addComponent(tilePosComp);
    entity->addComponent(healthComp);
    entity->addComponent(attackComp);
    entity->addComponent(laserComp);

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }

  static Entity *addWall(Game *game, System *system, int tileX,
                               int tileY) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp = Graphics(convertColorType(0xFFFFFFFF));
    auto shapeComp = Shape(16, 16);
    auto tilePosComp = TilePosition(tileX, tileY);
    auto healthComp = Health(500, 2);

    entity->addComponent(graphicsComp);
    entity->addComponent(shapeComp);
    entity->addComponent(tilePosComp);
    entity->addComponent(healthComp);

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }

  static Entity *addEnemy(Game *game, System *system, double x,
                               double y) {
    auto entity = std::make_unique<Entity>(system);

    auto graphicsComp = Graphics(convertColorType(0xFFC06060));
    auto shapeComp = Shape(16, 16);
    auto positionComp = Position(x, y);
    auto physicsComp = Physics();
    auto healthComp = Health(10, 0);
    auto attackComp = Attack(1, 3, 0.5, Attack::FIGHTER);
    auto laserComp = LaserShooter();
    auto pathingComp = Pathing();

    entity->addComponent(graphicsComp);
    entity->addComponent(shapeComp);
    entity->addComponent(positionComp);
    entity->addComponent(physicsComp);
    entity->addComponent(healthComp);
    entity->addComponent(attackComp);
    entity->addComponent(laserComp);
    entity->addComponent(pathingComp);

    auto pt = entity.get();
    system->addEntity(game, std::move(entity));

    return pt;
  }
};
