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
  int m_entID;
  bool m_alive = true;
  virtual void update(Game *game, System *system) {};
};
