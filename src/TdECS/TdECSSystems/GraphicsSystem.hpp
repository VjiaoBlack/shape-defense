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
#include "TdECS/TdECSComponents/Shape.hpp"

#include "TdECS/TdECSComponents/Graphics.hpp"
#include "SystemUtils.hpp"

class Game;

class GraphicsSystem {
 public:
  std::vector<std::unique_ptr<Graphics>> m_graphicsComponents;

  void update(Game *game, System* system) {
    updateComponents(game, system, m_graphicsComponents);
  }
};
