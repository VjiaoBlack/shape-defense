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
#include "ECS/Components/Shape.hpp"
#include "ECS/Components/Graphics.hpp"
#include "SystemUtils.hpp"

class Game;

class GraphicsSystem {
 public:
  std::array<Graphics, k_MAX_ENTS> m_graphicsComponents;

  void update(Game *game, System* system);
};
