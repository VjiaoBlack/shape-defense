#pragma once

/**
 * TrMainMenuLoop.hpp
 */

#include <string>
#include <vector>

#include "RenderLoop.hpp"

class Game;
class GUIEntity;
class GUISystem;

class MainMenuLoop : public RenderLoop {
 public:
  std::string m_titleText = "Defense";
  MY_Color    textColor0  = {0, 255, 0, 255};
  int         text_width;
  int         text_height;

  unique_ptr<GUISystem>  m_GUISystem;
  GUIEntity             *m_GUIMenu;

  explicit MainMenuLoop(Game *game);

  ~MainMenuLoop() override;

  RenderLoop *update(Game *game) override;
  void        render(Game *game) override;
};