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
  enum AttackType {
    FIGHTER = 0,
    SHOOTER = 1,
    NONE    = 2,
    COUNT   = 3
  } m_type;

  int m_target = 0;  // 0 targets enemies, 1 targets player
  int m_targetEntID = -1;

  double m_damage = 5.0;
  double m_cooldown = 1.0;
  double m_curCooldown = 0;

  Attack(int target, double damage, double cooldown, AttackType type)
      : m_target(target), m_damage(damage), m_cooldown(cooldown), m_type(type) {}

  void damage(Game *game, System *system);

  virtual void update(Game *game, System *system);
};
