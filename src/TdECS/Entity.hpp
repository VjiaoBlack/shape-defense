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

#include "EntityType.hpp"

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

template<> struct classToInt<Attack>       { enum { value = 1 }; };
template<> struct classToInt<Health>       { enum { value = 2 }; };
template<> struct classToInt<LaserShooter> { enum { value = 3 }; };
template<> struct classToInt<Pathing>      { enum { value = 4 }; };
template<> struct classToInt<Physics>      { enum { value = 5 }; };
template<> struct classToInt<TilePosition> { enum { value = 6 }; };
template<> struct classToInt<Position>     { enum { value = 7 }; };
template<> struct classToInt<Shape>        { enum { value = 8 }; };
template<> struct classToInt<Graphics>     { enum { value = 9 }; };

class MissingComponentException : public std::runtime_error {
 public:
  MissingComponentException(const std::string &__arg)
      : runtime_error(__arg) {}
};

class Entity {
 public:
  static uint numCreated[static_cast<uint>(EntityType::COUNT)+1];
  static uint numDestroyed[static_cast<uint>(EntityType::COUNT)+1];

  bool       m_alive = true;
  int        m_id;
  EntityType m_type;

  // add component pointers to this tuple later
  // TODO: restrict m_components access
  std::array<Component*, 10> m_components;
  System*                    m_system;

  Entity() {
    m_alive = false;
    m_id = 0;
  }

  // TODO: should I inline
  glm::dvec2 getPosition();
  glm::dvec2 getCenterPosition();

  template <class T>
  void addComponent(T component);

  void die();

  template <class T>
  inline T *get() {
    return static_cast<T *>(m_components[classToInt<T>::value]);
  }

  template <class T>
  inline bool has() {
    return m_components[classToInt<T>::value] != nullptr;
  }

  template<EntityType, typename...Args>
  static void addEntity(Game* game, System* system, Args...args);

  template<typename...Args>
  static void addEntity(Game* game, System* system, EntityType type, Args...args);

 private:
  Entity(System *system, EntityType type);
};
