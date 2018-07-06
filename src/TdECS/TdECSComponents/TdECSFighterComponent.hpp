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
//  int m_target = 1;  // 0 targets enemies, 1 targets player
//  int m_targetEntID = -1;
//
//  double m_damage;
//  double m_cooldown;
//  double m_laserDuration = 0.1;
//  double m_range;
//
//  bool m_isShooting = false;
//  double m_curCooldown = 0;
//  double m_curLaserDuration = 0;

//  TdECSFighterComponent(double damage, double cooldown, double range)
//      : m_damage(damage), m_cooldown(cooldown), m_range(range) {}
  TdECSFighterComponent() {};

  virtual void update(TdGame *game, TdECSSystem *system);
};

