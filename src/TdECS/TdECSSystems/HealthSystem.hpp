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
  std::vector<std::unique_ptr<Health>> m_healthComponents;
  std::vector<Health> m_healthComponentsTEMP;

  void update(Game *game, System* system);
};
