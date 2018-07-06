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
  TdECSFighterComponent() {};

  virtual void update(TdGame *game, TdECSSystem *system);
};

