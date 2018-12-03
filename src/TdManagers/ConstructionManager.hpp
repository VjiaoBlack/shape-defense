#pragma once
#include <SDL_rect.h>
/**
 * TdConstructionManager.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class Game;

class ConstructionManager {
 public:
  SDL_Rect m_rect    = {0, 0, 32, 32};
  bool     m_isOn    = false;
  bool     m_isTower = true;

  ConstructionManager() {}

  void update(Game* game);
  void build (Game* game); // right now just builds a tower

};

