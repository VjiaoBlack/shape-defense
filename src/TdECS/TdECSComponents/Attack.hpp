#pragma once
/**
 * TdECSAttackComponent.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */
#include "Component.hpp"

class Attack : public Component {
 public:
  enum AttackType {
    NONE    = 0,
    FIGHTER = 1,
    SHOOTER = 2
  } m_type;

  enum Team {
    NEUTRAL = 0,
    ALLIED  = 1,
    ENEMY   = 2
  } m_team;

  int m_targetEntID = -1;

  double m_damage = 5.0;
  double m_cooldown = 1.0;
  double m_curCooldown = 0;

  Attack() {}
  Attack(Team team, double damage, double cooldown, AttackType type)
      : m_team(team), m_damage(damage), m_cooldown(cooldown), m_type(type) {}

  void damage(Game *game, System *system);
};
