#pragma once
/**
 * HeatMapManager.hpp
 *
 * Victor Jiao
 *
 * <DETAILS>
 */

#define GLM_FORCE_PURE


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
  std::array<float, World::size> m_tiles;

  std::array<float, World::size> m_tmp;

  HeatMapManager(Game* game);

  void update(Game* game);
};

