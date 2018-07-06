#pragma once
/**
 * TdECSLaserShooterComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSLaserShooterComponent : public TdECSComponent {
 public:
  double m_laserDuration = 0.1;

  bool m_isShooting = false;
  double m_curLaserDuration = 0;

  void fire() {
    m_curLaserDuration = m_laserDuration;
    m_isShooting = true;
  }

  TdECSLaserShooterComponent() {}

  virtual void update(TdGame *game, TdECSSystem *system);
};
