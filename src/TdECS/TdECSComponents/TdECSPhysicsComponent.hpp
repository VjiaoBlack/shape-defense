#pragma once
/**
 * TdECSPhysicsComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSPhysicsComponent : public TdECSComponent {
 public:
  double m_vx = 0.0;
  double m_vy = 0.0;
  double m_vtheta = 0.0;

  TdECSPhysicsComponent() {}

  virtual void update(TdGame *game, TdECSSystem *system);
};
