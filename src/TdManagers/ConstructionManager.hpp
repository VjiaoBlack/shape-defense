#pragma once
/**
 * TdConstructionManager.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

#include <SDL_rect.h>
#include "../TdECS/EntityType.hpp"

class Game;

class ConstructionManager {
 public:
  SDL_Rect   m_rect    = {0, 0, 32, 32};
  bool       m_isOn    = false;
  bool       m_isTower = true;
  EntityType m_type    = EntityType::NONE;

  ConstructionManager() {}

  void update(Game* game);
  void build (Game* game); // right now just builds a tower

};

