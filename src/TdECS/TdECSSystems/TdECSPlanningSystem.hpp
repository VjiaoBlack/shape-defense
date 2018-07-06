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
#include "TdECS/TdECSComponents/TdECSPathingComponent.hpp"
#include "TdECS/TdECSComponents/TdECSAttackComponent.hpp"
#include "TdECS/TdECSComponents/TdECSLaserShooterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"
#include "TdECSSystemUtils.hpp"

class TdGame;

class TdECSPlanningSystem {
 public:
  std::vector<std::unique_ptr<TdECSShooterComponent>> m_shooterComponents;
  std::vector<std::unique_ptr<TdECSFighterComponent>> m_fighterComponents;

  std::vector<std::unique_ptr<TdECSPathingComponent>> m_pathingComponents;

  std::vector<std::unique_ptr<TdECSAttackComponent>> m_attackComponents;
  std::vector<std::unique_ptr<TdECSLaserShooterComponent>> m_laserComponents;

  void update(TdGame *game, TdECSSystem* system) {
    updateComponents(game, system, m_shooterComponents);
    updateComponents(game, system, m_fighterComponents);

    updateComponents(game, system, m_attackComponents);
    updateComponents(game, system, m_laserComponents);

    updateComponents(game, system, m_pathingComponents);
  }
};
