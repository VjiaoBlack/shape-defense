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

class TdGame;

class TdECSGraphicsSystem {
 public:
  std::vector<std::unique_ptr<TdECSGraphicsComponent>> m_graphicsComponents;

  void update(TdGame *game) {
    for (auto &c : m_graphicsComponents) {
      c->update(game);
    }
  }
};
