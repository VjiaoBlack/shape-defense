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

  int m_targetEntId = -1;

  TdECSFighterComponent() {}

  virtual void update(TdGame *game, TdECSSystem *system);
};

