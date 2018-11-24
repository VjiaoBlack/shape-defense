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



class PlanningSystem {
 public:
  std::vector<std::unique_ptr<Pathing>> m_pathingComponents;

  std::vector<std::unique_ptr<Attack>> m_attackComponents;
  std::vector<std::unique_ptr<LaserShooter>> m_laserComponents;

  void update(Game *game, System* system);
};
