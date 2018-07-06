#pragma once
/**
 * TdECSComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class TdECSEntity;
class TdGame;
class TdECSSystem;

class TdECSComponent {
 public:
  int m_entID;
  bool m_dead = false;
  virtual void update(TdGame *game, TdECSSystem *system) {};
};
