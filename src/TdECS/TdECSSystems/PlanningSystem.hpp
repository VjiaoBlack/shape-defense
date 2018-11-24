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

  std::vector<Pathing> m_pathingComponentsTEMP;
  std::vector<Attack> m_attackComponentsTEMP;
  std::vector<LaserShooter> m_laserComponentsTEMP;

  void update(Game *game, System* system);
};
