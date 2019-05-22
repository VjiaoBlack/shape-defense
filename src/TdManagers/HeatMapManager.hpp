#pragma once
/**
 * HeatMapManager.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

//#include <ECS/EntityType.hpp>
//#include <GUI/Systems/GUISystem.hpp>
//#include <GUI/GUIEntity.hpp>

#include <glm/glm.hpp>
#include <map>
#include <Graphics.hpp>

class Game;

class HeatMapManager {
 public:
  // some storage mechanism for tiles
  std::array<double, 56*56> m_tiles;

  std::array<double, 56*56> m_tmp;

  std::array<Triangle, 56*56> m_vis;

  HeatMapManager(Game* game);

  void update(Game* game);
};

