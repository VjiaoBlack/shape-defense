#pragma once
/**
 * TdECSComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class Entity;
class Game;
class System;

class Component {
 public:
  int m_entID = 0;

  // TODO: default to false
  bool m_alive = false;
  virtual void update(Game *game, System *system) {};
};
