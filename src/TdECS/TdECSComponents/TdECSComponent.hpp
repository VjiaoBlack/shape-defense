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
  virtual void update(TdGame* game) {};
};
