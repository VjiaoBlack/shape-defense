#pragma once
/**
 * TdECSHealthComponent.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "TdECSComponent.hpp"

class TdECSHealthComponent : public TdECSComponent {
 public:
  double m_curHealth;
  double m_maxHealth;
  double m_armor;

  TdECSHealthComponent(double health, double armor)
      : m_curHealth(health), m_maxHealth(health), m_armor(armor) {}

  virtual void update(TdGame *game, TdECSSystem *system);
};
