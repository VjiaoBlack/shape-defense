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
#include "TdECS/TdECSComponents/Fighter.hpp"
#include "TdECS/TdECSComponents/Health.hpp"
#include "TdECS/TdECSComponents/Shooter.hpp"
#include "SystemUtils.hpp"

class Game;

class HealthSystem {
 public:
  std::vector<std::unique_ptr<Health>> m_healthComponents;

  void update(Game *game, System* system) {
    updateComponents(game, system, m_healthComponents); // updates health
    updateComponents(game, system, m_healthComponents); // removes dead health comps
  }
};
