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

class TdECSComponent {
 public:
  TdECSEntity* m_ent;
  bool m_dead = false;
  virtual void update(TdGame* game) {};
};
