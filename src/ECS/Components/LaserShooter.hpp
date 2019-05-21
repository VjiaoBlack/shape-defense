#pragma once
/**
 * TdECSLaserShooterComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"

class LaserShooter : public Component {
 public:
  double m_laserDuration = 0.1;

  bool m_isShooting = false;
  double m_curLaserDuration = 0;

  inline void fire() {
    m_curLaserDuration = m_laserDuration;
    m_isShooting = true;
  }

  LaserShooter() {}
};
