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
  SDL_Rect m_rect;
  bool m_isOn = false;
  bool m_isTower = true;

  ConstructionManager() {
    m_rect.x = 0;
    m_rect.y = 0;
    m_rect.w = 32;
    m_rect.h = 32;
  }

  void update(Game* game);

  void build(Game* game); // right now just builds a tower

};

