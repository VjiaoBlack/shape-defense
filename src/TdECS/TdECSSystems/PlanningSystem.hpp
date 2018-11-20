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
#include "TdECS/TdECSComponents/Pathing.hpp"
#include "TdECS/TdECSComponents/Attack.hpp"
#include "TdECS/TdECSComponents/LaserShooter.hpp"
#include "TdECS/TdECSComponents/Fighter.hpp"
#include "TdECS/TdECSComponents/Health.hpp"
#include "TdECS/TdECSComponents/Shooter.hpp"
#include "SystemUtils.hpp"

class Game;

class PlanningSystem {
 public:
  std::vector<std::unique_ptr<Shooter>> m_shooterComponents;
  std::vector<std::unique_ptr<Fighter>> m_fighterComponents;

  std::vector<std::unique_ptr<Pathing>> m_pathingComponents;

  std::vector<std::unique_ptr<Attack>> m_attackComponents;
  std::vector<std::unique_ptr<LaserShooter>> m_laserComponents;

  void update(Game *game, System* system) {
    updateComponents(game, system, m_shooterComponents);
    updateComponents(game, system, m_fighterComponents);

    updateComponents(game, system, m_attackComponents);
    updateComponents(game, system, m_laserComponents);

    updateComponents(game, system, m_pathingComponents);
  }
};
