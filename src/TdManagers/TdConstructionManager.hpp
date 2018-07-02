#pragma once
#include <SDL_rect.h>
/**
 * TdConstructionManager.hpp
 *  
 * Victor Jiao
 *
 * <DETAILS>
 */

class TdGame;

class TdConstructionManager {
 public:
  SDL_Rect m_rect;
  bool m_isOn = false;
  int m_cooldown = 0;

  TdConstructionManager() {
    m_rect.x = 0;
    m_rect.y = 0;
    m_rect.w = 33;
    m_rect.h = 33;
  }

  void update(TdGame* game);
  void build(TdGame* game); // right now just builds a tower

};

