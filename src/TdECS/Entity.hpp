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

//#include "TdECS/TdECSSystems/System.hpp"

class Component;

template<typename T>
struct classToInt { enum { value = 0 }; };

class Attack;
class Health;
class LaserShooter;
class Pathing;
class Physics;
class TilePosition;
class Position;
class Shape;
class Graphics;

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

  // todo should i inline
  glm::dvec2 getPosition();

  glm::dvec2 getCenterPosition();

//  inline glm::dvec2 getPosition() {
//    if (this->has<TilePosition>()) {
//      return this->get<TilePosition>()->m_xy * 16 +
//             glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2;
//    } else if (this->has<Position>()) {
//      return glm::dvec2(this->get<Position>()->m_p);
//    } else {
//      std::string msg = "missing component: general position";
//      throw MissingComponentException(msg);
//    }
//  };
//
//  inline glm::dvec2 getCenterPosition() {
//    if (this->has<TilePosition>()) {
//      return this->get<TilePosition>()->m_xy * 16 +
//             glm::ivec2(K_DISPLAY_SIZE_X, K_DISPLAY_SIZE_Y) / 2 +
//             glm::ivec2(this->get<Shape>()->m_dimensions / 2.0);
//    } else if (this->has<Position>()) {
//      return this->get<Position>()->m_p +
//             this->get<Shape>()->m_dimensions / 2.0;
//    } else {
//      std::string msg = "missing component: general position";
//      throw MissingComponentException(msg);
//    }
//  };

  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::map<int, Component *> m_components;
  System *m_system;

  Entity() {
    m_alive = false;
    m_id = 0;
  }
//  Entity() = delete;
  Entity(System *GUISystem);

  template <class T>
  void addComponent(T component);

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

  static Entity *addPlayerBase(Game *game, System *system);

  static Entity *addTower(Game *game, System *system, int tileX,
                               int tileY);

  static Entity *addWall(Game *game, System *system, int tileX,
                               int tileY);

  static Entity *addEnemy(Game *game, System *system, double x,
                               double y);
};
