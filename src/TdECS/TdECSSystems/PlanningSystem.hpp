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
  std::array<Pathing, 1000> m_pathingComponents;
  std::array<Attack, 1000> m_attackComponents;
  std::array<LaserShooter, 1000> m_laserComponents;

  void update(Game *game, System* system);
};
