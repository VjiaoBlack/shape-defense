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
#include "ECS/Components/Health.hpp"
#include "SystemUtils.hpp"

class Game;

class HealthSystem {
 public:
  std::array<Health, k_MAX_ENTS> m_healthComponents;

  void update(Game *game, System* system);
};
