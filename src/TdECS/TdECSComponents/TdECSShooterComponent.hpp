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
//  int m_target = 0;  // 0 targets enemies, 1 targets player
//  int m_targetEntID;
//
//  double m_damage;
//  double m_cooldown;
//  double m_laserDuration = 0.1;
//  double m_range;
//
//  bool m_isShooting = false;
//  double m_curCooldown = 0;
//  double m_curLaserDuration = 0;

  TdECSShooterComponent() {};
  virtual void update(TdGame *game, TdECSSystem *system);
};
