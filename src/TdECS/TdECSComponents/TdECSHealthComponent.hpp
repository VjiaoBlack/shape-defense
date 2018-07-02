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
  double m_health;
  double m_armor;

  TdECSHealthComponent(double health, double armor)
      : m_health(health), m_armor(armor) {}

  virtual void update(TdGame* game);
};
