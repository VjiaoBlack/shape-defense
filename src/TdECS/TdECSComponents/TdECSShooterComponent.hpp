#pragma once
/**
 * TdECSShooterComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSShooterComponent : public TdECSComponent {
 public:
  TdECSShooterComponent() {};
  virtual void update(TdGame *game, TdECSSystem *system);
};
