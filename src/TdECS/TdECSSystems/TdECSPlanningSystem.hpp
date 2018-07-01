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

class TdGame;

class TdECSPlanningSystem {
 public:
  std::vector<std::unique_ptr<TdECSShooterComponent>> m_shooterComponents;
  std::vector<std::unique_ptr<TdECSFighterComponent>> m_fighterComponents;
  std::vector<std::unique_ptr<TdECSHealthComponent>> m_healthComponents;

  void update(TdGame *game) {
    for (auto &c : m_shooterComponents) {
      c->update(game);
    }
    for (auto &c : m_fighterComponents) {
      c->update(game);
    }
    for (auto &c : m_healthComponents) {
      c->update(game);
    }
  }
};
