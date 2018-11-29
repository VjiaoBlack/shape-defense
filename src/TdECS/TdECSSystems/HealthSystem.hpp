#pragma once
/**
 * TdECSHealthSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>
#include "TdECS/TdECSComponents/Health.hpp"
#include "SystemUtils.hpp"

class Game;

class HealthSystem {
 public:
  std::array<Health, 1000> m_healthComponents;

  void update(Game *game, System* system);
};
