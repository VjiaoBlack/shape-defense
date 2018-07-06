#pragma once
#include "TdECSComponent.hpp"
/**
 * TdECSAttackComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class TdECSAttackComponent : public TdECSComponent {
 public:
  int m_target = 0;  // 0 targets enemies, 1 targets player
  int m_targetEntID = -1;

  double m_damage = 5.0;
  double m_cooldown = 1.0;
  double m_curCooldown = 0;

  TdECSAttackComponent(int target, double damage, double cooldown) : m_target(target), m_damage
  (damage),
  m_cooldown
      (cooldown) {}

  void damage(TdGame *game, TdECSSystem *system);

  virtual void update(TdGame *game, TdECSSystem *system);
};
