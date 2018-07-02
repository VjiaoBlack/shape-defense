#pragma once
/** 
 * TdECSGraphicsSystem.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <memory>
#include <vector>
#include "TdECS/TdECSComponents/TdECSShapeComponent.hpp"

#include "TdECS/TdECSComponents/TdECSGraphicsComponent.hpp"
#include "TdECSSystemUtils.hpp"

class TdGame;

class TdECSGraphicsSystem {
 public:
  std::vector<std::unique_ptr<TdECSGraphicsComponent>> m_graphicsComponents;

  void update(TdGame *game, TdECSSystem* system) {
    updateComponents(game, system, m_graphicsComponents);
  }
};
