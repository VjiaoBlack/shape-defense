#pragma once
/**
 * TdECSPhysicsSystem.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>

#include "TdECS/TdECSComponents/TdECSPhysicsComponent.hpp"
#include "TdECS/TdECSComponents/TdECSPositionComponent.hpp"

class TdGame;

class TdECSPhysicsSystem {
 public:
  std::vector<std::unique_ptr<TdECSPositionComponent>> m_positionComponents;
  std::vector<std::unique_ptr<TdECSPhysicsComponent>> m_physicsComponents;

  void update(TdGame *game) {
    for (auto &c : m_physicsComponents) {
      c->update(game);
    }
  }
};
