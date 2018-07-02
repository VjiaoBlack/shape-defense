#pragma once
/**
 * TdECSPlanningSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"
#include "TdECSSystemUtils.hpp"

class TdGame;

class TdECSPlanningSystem {
 public:
  std::vector<std::unique_ptr<TdECSShooterComponent>> m_shooterComponents;
  std::vector<std::unique_ptr<TdECSFighterComponent>> m_fighterComponents;

  void update(TdGame *game, TdECSSystem* system) {
    updateComponents(game, system, m_shooterComponents);
    updateComponents(game, system, m_fighterComponents);
  }
};
