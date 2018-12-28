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
#include "../TdGUI/TdGUISystems/GUISystem.hpp"
#include "../TdGUI/GUIEntity.hpp"

class Game;

class ConstructionManager {
 public:
  SDL_Rect   m_rect = {0, 0, 32, 32};
  bool       m_isOn = false;
  EntityType m_type = EntityType::TOWER;

  unique_ptr<GUISystem> m_GUISystem;
  GUIEntity *m_GUIMenu;

  ConstructionManager(Game* game);

  void update(Game* game);
  void render(Game* game);
  void build (Game* game); // right now just builds a tower

};

