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
  std::array<Pathing, k_MAX_ENTS> m_pathingComponents;
  std::array<Attack, k_MAX_ENTS> m_attackComponents;
  std::array<LaserShooter, k_MAX_ENTS> m_laserComponents;

  void update(Game *game, System* system);
};
