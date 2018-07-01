#pragma once
/**
 * TdECSFighterComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSFighterComponent : public TdECSComponent {
 public:
  int m_target = 1;

  bool m_fighting = false;

  TdECSEntity* m_targetEnt = nullptr;

  TdECSFighterComponent() {}

  virtual void update(TdGame* game);
};

