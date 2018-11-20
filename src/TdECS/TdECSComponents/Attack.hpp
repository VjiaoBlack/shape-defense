#pragma once
#include "Component.hpp"
/**
 * TdECSAttackComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class Attack : public Component {
 public:
  int m_target = 0;  // 0 targets enemies, 1 targets player
  int m_targetEntID = -1;

  double m_damage = 5.0;
  double m_cooldown = 1.0;
  double m_curCooldown = 0;

  Attack(int target, double damage, double cooldown) : m_target(target), m_damage
  (damage),
  m_cooldown
      (cooldown) {}

  void damage(Game *game, System *system);

  virtual void update(Game *game, System *system);
};
