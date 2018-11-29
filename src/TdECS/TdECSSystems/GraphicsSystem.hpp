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

class Game;

class GraphicsSystem {
 public:
  std::array<Graphics, 1000> m_graphicsComponents;

  void update(Game *game, System* system);
};
