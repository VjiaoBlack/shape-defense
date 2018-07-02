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
#include "TdECS/TdECSComponents/TdECSFighterComponent.hpp"
#include "TdECS/TdECSComponents/TdECSHealthComponent.hpp"
#include "TdECS/TdECSComponents/TdECSShooterComponent.hpp"
#include "TdECSSystemUtils.hpp"

class TdGame;

class TdECSHealthSystem {
 public:
  std::vector<std::unique_ptr<TdECSHealthComponent>> m_healthComponents;

  void update(TdGame *game) {
    updateComponents(game, m_healthComponents); // updates health
    updateComponents(game, m_healthComponents); // removes dead health comps
  }
};
