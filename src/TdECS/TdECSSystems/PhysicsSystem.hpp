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
  std::array<Position, k_MAX_ENTS> m_positionComponents;
  std::array<Physics, k_MAX_ENTS>  m_physicsComponents;


  void update(Game *game, System* system);
};
