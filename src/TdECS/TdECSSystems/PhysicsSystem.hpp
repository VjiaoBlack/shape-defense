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

#include "TdECS/TdECSComponents/Physics.hpp"
#include "TdECS/TdECSComponents/Position.hpp"
#include "SystemUtils.hpp"

class Game;

class PhysicsSystem {
 public:
  // don't need to update position components?
  std::vector<std::unique_ptr<Position>> m_positionComponents;
  std::vector<std::unique_ptr<Physics>>  m_physicsComponents;

  void update(Game *game, System* system);
};
