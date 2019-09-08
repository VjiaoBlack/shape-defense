#pragma once
/**
 * Health.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include "Component.hpp"

class Health : public Component {
 public:
  double m_curHealth;
  double m_maxHealth;
  double m_armor;

  Health() {}
  Health(double health, double armor)
      : m_curHealth(health), m_maxHealth(health), m_armor(armor) {}

  void update(Game *game, System *system);
};
